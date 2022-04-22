#pragma once

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    class WinEventData
    {
        public:

        Player const winner;

        explicit WinEventData(Player const winner);
    };
}
