#pragma once

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    class CellFallThroughEventData
    {
        public:

        connect_four::Player const player;
        uint_least8_t const row;
        uint_least8_t const col;
        bool const is_final_position;

        CellFallThroughEventData(
            connect_four::Player const player,
            uint_least8_t const row,
            uint_least8_t const col,
            bool const is_final_position);
    };
}
