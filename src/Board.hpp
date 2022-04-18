#pragma once

#include <cstdint>
#include <vector>

#include "Player.hpp"
#include "Position.hpp"

namespace connect_four
{
    class Board
    {
        uint_least8_t _row_count;
        uint_least8_t _col_count;
        std::vector<std::vector<std::pair<Player, bool>>> _cells;

        public:

        Board(uint_least8_t row_count, uint_least8_t col_count);

        bool is_inbound(Position position);
        bool is_empty(Position position);
        bool is_filled(Position position, Player player);
        void set(Position position, Player player);
    };
}
