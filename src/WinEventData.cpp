#include "WinEventData.hpp"

#include "Player.hpp"

namespace connect_four
{
    WinEventData::WinEventData(Player const winner) : winner(winner)
    { }
}
