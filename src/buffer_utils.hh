#ifndef buffer_utils_hh_INCLUDED
#define buffer_utils_hh_INCLUDED

#include "buffer.hh"
#include "selection.hh"

#include "unicode.hh"
#include "utf8_iterator.hh"

namespace Kakoune
{
inline String content(const Buffer &buffer, const Selection &range)
{
    return buffer.string(range.min(), buffer.char_next(range.max()));
}

inline ByteCoord erase(Buffer &buffer, const Selection &range)
{
    return buffer.erase(range.min(), buffer.char_next(range.max()));
}

inline ByteCoord replace(Buffer &buffer, const Selection &range,
                         StringView content)
{
    return buffer.replace(range.min(), buffer.char_next(range.max()), content);
}

inline CharCount char_length(const Buffer &buffer, const Selection &range)
{
    return utf8::distance(buffer.iterator_at(range.min()),
                          buffer.iterator_at(buffer.char_next(range.max())));
}

inline bool is_bol(ByteCoord coord) { return coord.column == 0; }
inline bool is_eol(const Buffer &buffer, ByteCoord coord)
{
    return buffer.is_end(coord) or
           buffer[coord.line].length() == coord.column + 1;
}

inline bool is_bow(const Buffer &buffer, ByteCoord coord)
{
    auto it = utf8::iterator<BufferIterator>(buffer.iterator_at(coord), buffer);
    if (coord == ByteCoord{0, 0}) return is_word(*it);

    return not is_word(*(it - 1)) and is_word(*it);
}

inline bool is_eow(const Buffer &buffer, ByteCoord coord)
{
    if (buffer.is_end(coord) or coord == ByteCoord{0, 0}) return true;

    auto it = utf8::iterator<BufferIterator>(buffer.iterator_at(coord), buffer);
    return is_word(*(it - 1)) and not is_word(*it);
}

CharCount get_column(const Buffer &buffer, CharCount tabstop, ByteCoord coord);

ByteCount get_byte_to_column(const Buffer &buffer, CharCount tabstop,
                             CharCoord coord);

Buffer *create_fifo_buffer(String name, int fd, bool scroll = false);
Buffer *open_file_buffer(StringView filename);
Buffer *open_or_create_file_buffer(StringView filename);
void reload_file_buffer(Buffer &buffer);

void write_to_debug_buffer(StringView str);
}

#endif  // buffer_utils_hh_INCLUDED
