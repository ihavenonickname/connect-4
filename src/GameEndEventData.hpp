#pragma once

class Game;

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    class GameEndEventData
    {
        friend class Game;

        connect_four::Player _winner;

        public:
        connect_four::Player winner();
    };
}
