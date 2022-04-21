#include "Board.hpp"

#include <cstdint>

#include "Player.hpp"
#include "Position.hpp"

namespace connect_four
{
    #define at(position) (this->_cells[static_cast<std::size_t>(position.row())][static_cast<std::size_t>(position.col())])

    Board::Board(uint_least8_t row_count, uint_least8_t col_count)
    {
        this->_row_count = row_count;
        this->_col_count = col_count;

        auto empty = std::make_pair(Player::PLAYER_1, false);
        auto row = std::vector<std::pair<Player, bool>>(col_count, empty);

        this->_cells.resize(row_count, row);
    }

    bool Board::is_inside(Position position)
    {
        return
            position.row() >= 0 &&
            position.col() >= 0 &&
            position.row() < this->_row_count &&
            position.col() < this->_col_count;
    }

    bool Board::is_empty(Position position)
    {
        return this->is_inside(position) && !at(position).second;
    }

    bool Board::is_filled(Position position, Player player)
    {
        return
            this->is_inside(position) &&
            at(position).second &&
            at(position).first == player;
    }

    void Board::set(Position position, Player player)
    {
        at(position) = std::make_pair(player, true);
    }
}
