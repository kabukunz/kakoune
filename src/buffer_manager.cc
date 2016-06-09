#include "buffer_manager.hh"

#include "assert.hh"
#include "buffer.hh"
#include "client_manager.hh"
#include "containers.hh"
#include "exception.hh"
#include "file.hh"
#include "string.hh"

namespace Kakoune {

struct name_not_unique : runtime_error {
  name_not_unique() : runtime_error("buffer name is already in use") {}
};

BufferManager::~BufferManager() {
  // Make sure not clients exists
  ClientManager::instance().clear();
}

Buffer* BufferManager::create_buffer(String name,
                                     Buffer::Flags flags,
                                     StringView data,
                                     timespec fs_timestamp) {
  auto path = real_path(parse_filename(name));
  for (auto& buf : m_buffers) {
    if (buf->name() == name or
        (buf->flags() & Buffer::Flags::File and buf->name() == path))
      throw name_not_unique();
  }

  m_buffers.emplace(m_buffers.begin(),
                    new Buffer{std::move(name), flags, data, fs_timestamp});
  return m_buffers.front().get();
}

void BufferManager::delete_buffer(Buffer& buffer) {
  auto it = find_if(m_buffers, [&](const std::unique_ptr<Buffer>& p) {
    return p.get() == &buffer;
  });
  kak_assert(it != m_buffers.end());

  ClientManager::instance().ensure_no_client_uses_buffer(buffer);

  m_buffer_trash.emplace_back(std::move(*it));
  m_buffers.erase(it);
}

Buffer* BufferManager::get_buffer_ifp(StringView name) {
  auto path = real_path(parse_filename(name));
  for (auto& buf : m_buffers) {
    if (buf->name() == name or
        (buf->flags() & Buffer::Flags::File and buf->name() == path))
      return buf.get();
  }
  return nullptr;
}

Buffer& BufferManager::get_buffer(StringView name) {
  Buffer* res = get_buffer_ifp(name);
  if (not res)
    throw runtime_error(format("no such buffer '{}'", name));
  return *res;
}

void BufferManager::backup_modified_buffers() {
  for (auto& buf : m_buffers) {
    if ((buf->flags() & Buffer::Flags::File) and buf->is_modified())
      write_buffer_to_backup_file(*buf);
  }
}

void BufferManager::clear_buffer_trash() {
  for (auto& buffer : m_buffer_trash) {
    // Do that again, to be tolerant in some corner cases, where a buffer is
    // deleted during its creation
    ClientManager::instance().ensure_no_client_uses_buffer(*buffer);
    ClientManager::instance().clear_window_trash();

    buffer.reset();
  }

  m_buffer_trash.clear();
}
}
