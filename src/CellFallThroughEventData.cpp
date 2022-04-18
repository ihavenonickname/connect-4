#include "CellFallThroughEventData.hpp"

#include "Player.hpp"

namespace connect_four
{
    connect_four::Player CellFallThroughEventData::player()
    {
        return this->_player;
    }

    uint_least8_t CellFallThroughEventData::row()
    {
        return this->_row;
    }

    uint_least8_t CellFallThroughEventData::col()
    {
        return this->_col;
    }

    bool CellFallThroughEventData::is_final_position()
    {
        return this->_is_final_position;
    }
}
