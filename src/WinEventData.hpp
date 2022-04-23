#pragma once

#include "Game.hpp"
#include "Player.hpp"

namespace connect_four
{
    struct WinEventData
    {
        Player const winner;
    };
}
