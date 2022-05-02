#include "Board.hpp"

#include <cstdint>

#include "Player.hpp"
#include "Position.hpp"

namespace connect_four
{
    Board::Board(uint_least8_t const row_count, uint_least8_t const col_count):
        _row_count(row_count),
        _col_count(col_count),
        _cells(row_count * col_count)
    { }

    bool Board::is_inside(Position const position)
    {
        return
            position.row >= 0 &&
            position.col >= 0 &&
            position.row < _row_count &&
            position.col < _col_count;
    }

    bool Board::is_empty(Position const position)
    {
        return is_inside(position) && !_at(position).is_filled;
    }

    bool Board::is_filled(Position const position, Player const player)
    {
        return
            is_inside(position) &&
            _at(position).is_filled &&
            _at(position).player == player;
    }

    void Board::set(Position const position, Player const player)
    {
        _at(position) = Cell{player, true};
    }

    Cell & Board::_at(Position const & position)
    {
        auto index = position.row * _col_count + position.col;

        return _cells[static_cast<uint8_t>(index)];
    }
}
