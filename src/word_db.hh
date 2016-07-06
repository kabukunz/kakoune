#ifndef word_db_hh_INCLUDED
#define word_db_hh_INCLUDED

#include "buffer.hh"
#include "ranked_match.hh"
#include "shared_string.hh"
#include "unordered_map.hh"
#include "vector.hh"

namespace Kakoune
{
using RankedMatchList = Vector<RankedMatch>;

// maintain a database of words available in a buffer
class WordDB
{
   public:
    WordDB(const Buffer &buffer);
    WordDB(const WordDB &) = delete;
    WordDB(WordDB &&) = default;

    RankedMatchList find_matching(StringView str);

    int get_word_occurences(StringView word) const;

   private:
    void update_db();
    void add_words(StringView line);
    void remove_words(StringView line);

    struct WordInfo
    {
        StringDataPtr word;
        UsedLetters letters;
        int refcount;
    };
    using WordToInfo = UnorderedMap<StringView, WordInfo, MemoryDomain::WordDB>;
    using Lines = Vector<StringDataPtr, MemoryDomain::WordDB>;

    SafePtr<const Buffer> m_buffer;
    size_t m_timestamp;
    WordToInfo m_words;
    Lines m_lines;
};
}

#endif  // word_db_hh_INCLUDED
