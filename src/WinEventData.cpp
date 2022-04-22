#include "WinEventData.hpp"

#include "Player.hpp"

namespace connect_four
{
    connect_four::Player WinEventData::winner()
    {
        return this->_winner;
    }
}
