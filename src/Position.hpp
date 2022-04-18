#pragma once

#include <cstdint>

namespace connect_four
{
    class Position
    {
        int_least16_t _row;
        int_least16_t _col;

        public:

        Position(int_least16_t row, int_least16_t col);
        int_least16_t row();
        int_least16_t col();
        Position add_row(int_least16_t offset);
        Position add_col(int_least16_t offset);
    };
}
