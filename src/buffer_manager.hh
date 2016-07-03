#ifndef buffer_manager_hh_INCLUDED
#define buffer_manager_hh_INCLUDED

#include "buffer.hh"
#include "completion.hh"
#include "utils.hh"
#include "safe_ptr.hh"

namespace Kakoune
{

class ClientManager;


class BufferManager : public Singleton<BufferManager> {
public:
    using BufferList = Vector<std::unique_ptr<Buffer>>;
    using iterator = BufferList::const_iterator;
    ~BufferManager();

    Buffer* create_buffer(String name, Buffer::Flags flags,
                          StringView data = {},
                          timespec fs_timestamp = InvalidTime);

    void delete_buffer(Buffer& buffer);

    iterator begin() const { return m_buffers.cbegin(); }
    iterator end() const { return m_buffers.cend(); }
    size_t   count() const { return m_buffers.size(); }

    Buffer* get_buffer_ifp(StringView name);
    Buffer& get_buffer(StringView name);

    void backup_modified_buffers();
    void clear_buffer_trash();
private:
    BufferList m_buffers;
    BufferList m_buffer_trash;

    // ClientManager& client_manager() const;
    ClientManager* m_client_manager;
    bool has_client_manager() const { return (bool)m_client_manager; }
    void set_client_manager(ClientManager& client_manager);

};

}

#endif // buffer_manager_hh_INCLUDED
