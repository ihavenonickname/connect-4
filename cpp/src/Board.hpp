#pragma once

#include <cstdint>
#include <vector>

#include "Cell.hpp"
#include "Player.hpp"
#include "Position.hpp"

namespace connect_four
{
    class Board
    {
        uint_least8_t _row_count;
        uint_least8_t _col_count;
        std::vector<Cell> _cells;

        Cell & _at(Position const & position);

        public:

        Board(uint_least8_t const row_count, uint_least8_t const col_count);

        bool is_inside(Position const position);
        bool is_empty(Position const position);
        bool is_filled(Position const position, Player const player);
        void set(Position const position, Player const player);
    };
}
