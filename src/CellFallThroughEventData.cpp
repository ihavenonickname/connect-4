#include "CellFallThroughEventData.hpp"

#include "Player.hpp"

namespace connect_four
{
    CellFallThroughEventData::CellFallThroughEventData(
        Player const player,
        uint_least8_t const row,
        uint_least8_t const col,
        bool const is_final_position)
    :
        player(player),
        row(row),
        col(col),
        is_final_position(is_final_position)
    { }
}
