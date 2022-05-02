#pragma once

#include "Player.hpp"

namespace connect_four
{
    struct Cell
    {
        Player player;
        bool is_filled;
    };
}
