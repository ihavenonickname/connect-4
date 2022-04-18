#include "GameEndEventData.hpp"

#include "Player.hpp"

namespace connect_four
{
    connect_four::Player GameEndEventData::winner()
    {
        return this->_winner;
    }
}
