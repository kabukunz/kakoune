#ifndef line_and_column_hh_INCLUDED
#define line_and_column_hh_INCLUDED

#include "units.hh"

namespace Kakoune
{

template<typename EffectiveType, typename LineType, typename ColumnType>
struct LineAndColumn
{
    LineType   line;
    ColumnType column;

    constexpr LineAndColumn(LineType line = 0, ColumnType column = 0)
        : line(line), column(column) {}

    constexpr EffectiveType operator+(const EffectiveType& other) const
    {
        return EffectiveType(line + other.line, column + other.column);
    }

    constexpr EffectiveType& operator+=(const EffectiveType& other)
    {
        line   += other.line;
        column += other.column;
        return *static_cast<EffectiveType*>(this);
    }

    constexpr EffectiveType operator-(const EffectiveType& other) const
    {
        return EffectiveType(line - other.line, column - other.column);
    }

    EffectiveType& operator-=(const EffectiveType& other)
    {
        line   -= other.line;
        column -= other.column;
        return *static_cast<EffectiveType*>(this);
    }

    constexpr bool operator< (const EffectiveType& other) const
    {
        return (line != other.line) ? line < other.line
                                    : column < other.column;
    }

    constexpr bool operator<= (const EffectiveType& other) const
    {
        return (line != other.line) ? line < other.line
                                    : column <= other.column;
    }

    constexpr bool operator> (const EffectiveType& other) const
    {
        return (line != other.line) ? line > other.line
                                    : column > other.column;
    }

    constexpr bool operator>= (const EffectiveType& other) const
    {
        return (line != other.line) ? line > other.line
                                    : column >= other.column;
    }

    constexpr bool operator== (const EffectiveType& other) const
    {
        return line == other.line and column == other.column;
    }

    constexpr bool operator!= (const EffectiveType& other) const
    {
        return line != other.line or column != other.column;
    }
};

}

#endif // line_and_column_hh_INCLUDED
