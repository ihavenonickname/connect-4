#pragma once

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    class Game;

    class WinEventData
    {
        friend class Game;

        connect_four::Player _winner;

        public:
        connect_four::Player winner();
    };
}