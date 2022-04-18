#pragma once

class Game;

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    class CellFallThroughEventData
    {
        friend class Game;

        connect_four::Player _player;
        uint_least8_t _row;
        uint_least8_t _col;
        bool _is_final_position;

        public:
        connect_four::Player player();
        uint_least8_t row();
        uint_least8_t col();
        bool is_final_position();
    };
}
