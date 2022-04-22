#include "Game.hpp"

#include <cstdint>
#include <functional>
#include <vector>

#include "Board.hpp"
#include "CellFallThroughEventData.hpp"
#include "WinEventData.hpp"
#include "Player.hpp"
#include "PlayResult.hpp"
#include "Position.hpp"

namespace connect_four
{
    Game::Game(uint_least8_t row_count, uint_least8_t col_count)
        : _board(row_count, col_count)
    {
        this->_player = Player::PLAYER_1;
        this->_ended = false;
    }

    PlayResult Game::play(uint_least8_t col)
    {
        if (this->_ended)
        {
            return PlayResult::GAME_ALREADY_ENDED;
        }

        auto position = Position(0, col);

        if (!this->_board.is_inside(position))
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
                CellFallThroughEventData event_data;

                event_data._player = this->_player;
                event_data._row = row;
                event_data._col = col;
                event_data._is_final_position = is_final;

                handler(event_data);
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

            for (auto handler : this->_win_handlers)
            {
                WinEventData event_data;

                event_data._winner = this->_player;

                handler(event_data);
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

    void Game::on_event(std::function<void (CellFallThroughEventData)> handler)
    {
        this->_cell_fall_through_handlers.push_back(handler);
    }

    void Game::on_event(std::function<void (WinEventData)> handler)
    {
        this->_win_handlers.push_back(handler);
    }

    bool Game::_check_victory(Position position)
    {
        #define make_lambda(expr) [](Position pos, int_least16_t offset) { return expr; }

        auto _check = [this, position](std::function<Position (Position, int_least16_t)> f_next)
        {
            auto counter = 1;
            auto temp_pos = f_next(position, 1);

            while (this->_board.is_filled(temp_pos, this->_player))
            {
                temp_pos = f_next(temp_pos, 1);
                counter += 1;
            }

            temp_pos = f_next(position, -1);

            while (this->_board.is_filled(temp_pos, this->_player))
            {
                temp_pos = f_next(temp_pos, -1);
                counter += 1;
            }

            return counter >= 4;
        };

        auto vertial = make_lambda(pos.add_col(offset));
        auto horizontal = make_lambda(pos.add_row(offset));
        auto main_diag = make_lambda(pos.add_row(offset).add_col(offset));
        auto sec_diag = make_lambda(pos.add_row(-offset).add_col(offset));

        return _check(vertical) ||
            _check(horizontal) ||
            _check(main_diag) ||
            _check(sec_diag);
    }
}
