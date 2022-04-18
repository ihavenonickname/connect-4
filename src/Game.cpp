#include "Game.hpp"

#include <cstdint>
#include <functional>
#include <vector>

#include "Board.hpp"
#include "Player.hpp"
#include "PlayResult.hpp"
#include "Position.hpp"

namespace connect_four
{
    Game::Game(uint_least8_t row_count, uint_least8_t col_count, Player starting)
        : _board(row_count, col_count)
    {
        this->_player = starting;
        this->_ended = false;
    }

    PlayResult Game::play(uint_least8_t col)
    {
        if (this->_ended)
        {
            return PlayResult::GAME_ALREADY_ENDED;
        }

        auto position = Position(0, col);

        if (!this->_board.is_inbound(position))
        {
            return PlayResult::COLUMN_IS_INVALID;
        }

        if (!this->_board.is_empty(position))
        {
            return PlayResult::COLUMN_IS_FULL;
        }

        while (true)
        {
            auto row = static_cast<uint_least8_t>(position.row());
            auto col = static_cast<uint_least8_t>(position.col());
            auto next_pos = position.add_row(1);
            auto is_final = !this->_board.is_empty(next_pos);

            for (auto handler : this->_cell_fall_through_handlers)
            {
                handler(this->_player, row, col, is_final);
            }

            if (is_final)
            {
                break;
            }

            position = next_pos;
        }

        this->_board.set(position, this->_player);

        if (this->_check_victory(position))
        {
            this->_ended = true;

            for (auto handler : this->_game_ended_handlers)
            {
                handler(this->_player);
            }
        }
        else
        {
            this->_player =
                this->_player == Player::PLAYER_1
                ? Player::PLAYER_2
                : Player::PLAYER_1;
        }

        return PlayResult::SUCCESS;
    }

    void Game::on_event(CellFallThroughHandler handler)
    {
        this->_cell_fall_through_handlers.push_back(handler);
    }

    void Game::on_event(GameEndHandler handler)
    {
        this->_game_ended_handlers.push_back(handler);
    }

    bool Game::_check_victory(Position position)
    {
        // Check horizontally...

        auto counter = 1;
        auto temp_pos = position.add_col(1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_col(1);
            counter += 1;
        }

        temp_pos = position.add_col(-1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_col(-1);
            counter += 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // Check vertically...

        counter = 1;
        temp_pos = position.add_row(1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(1);
            counter += 1;
        }

        temp_pos = position.add_row(-1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(-1);
            counter += 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // Check main diagonal...

        counter = 1;
        temp_pos = position.add_row(1).add_col(1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(1).add_col(1);
            counter += 1;
        }

        temp_pos = position.add_row(-1).add_col(-1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(-1).add_col(-1);
            counter += 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // Check secondary diagonal...

        counter = 1;
        temp_pos = position.add_row(1).add_col(-1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(1).add_col(-1);
            counter += 1;
        }

        temp_pos = position.add_row(-1).add_col(1);

        while (this->_board.is_filled(temp_pos, this->_player))
        {
            temp_pos = temp_pos.add_row(-1).add_col(1);
            counter += 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        return false;
    }
}
