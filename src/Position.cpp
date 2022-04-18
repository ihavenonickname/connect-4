#include "Position.hpp"

#include <cstdint>

namespace connect_four
{
    Position::Position(int_least16_t row, int_least16_t col)
    {
        this->_row = row;
        this->_col = col;
    }

    int_least16_t Position::row()
    {
        return this->_row;
    }

    int_least16_t Position::col()
    {
        return this->_col;
    }

    Position Position::add_row(int_least16_t offset)
    {
        return Position(this->row() + offset, this->col());
    }

    Position Position::add_col(int_least16_t offset)
    {
        return Position(this->row(), this->col() + offset);
    }
}
