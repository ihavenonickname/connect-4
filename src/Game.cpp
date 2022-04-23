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

    PlayResult Game::play(uint_least8_t const col)
    {
        if (this->_ended)
        {
            return PlayResult::GAME_ALREADY_ENDED;
        }

        Position initial_position{0, col};

        if (!this->_board.is_inside(initial_position))
        {
            return PlayResult::COLUMN_IS_INVALID;
        }

        if (!this->_board.is_empty(initial_position))
        {
            return PlayResult::COLUMN_IS_FULL;
        }

        auto position = this->_fall_to_right_row(initial_position);

        this->_board.set(position, this->_player);

        if (this->_check_victory(position))
        {
            this->_ended = true;

            WinEventData event_data{this->_player};

            for (auto const & handler : this->_win_handlers)
            {
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

    void Game::on_event(std::function<void (CellFallThroughEventData)> const handler)
    {
        this->_cell_fall_through_handlers.push_back(handler);
    }

    void Game::on_event(std::function<void (WinEventData)> const handler)
    {
        this->_win_handlers.push_back(handler);
    }

    Position Game::_fall_to_right_row(Position position)
    {
        Position next_pos{static_cast<int_least16_t>(position.row + 1), position.col};
        auto is_final = !this->_board.is_empty(next_pos);

        CellFallThroughEventData event_data{
            this->_player,
            static_cast<uint_least8_t>(position.row),
            static_cast<uint_least8_t>(position.col),
            is_final
        };

        for (auto const & handler : this->_cell_fall_through_handlers)
        {
            handler(event_data);
        }

        return
            is_final
            ? position
            : this->_fall_to_right_row(next_pos);
    }

    bool Game::_check_victory(Position position)
    {
        auto _check = [this, position](std::function<Position (Position, int_least16_t)> f)
        {
            auto counter = 1;
            int_least16_t i = 1;

            while (this->_board.is_filled(f(position, i), this->_player))
            {
                counter += 1;
                i += 1;
            }

            i = -1;

            while (this->_board.is_filled(f(position, i), this->_player))
            {
                counter += 1;
                i -= 1;
            }

            return counter >= 4;
        };

        #define make_lambda(row, col) [](Position pos, int_least16_t i) \
        {                                                               \
            return Position{                                            \
                static_cast<int_least16_t>(row),                        \
                static_cast<int_least16_t>(col)};                       \
        }                                                               \

        return
            _check(make_lambda(pos.row    , pos.col + i)) ||
            _check(make_lambda(pos.row + i, pos.col    )) ||
            _check(make_lambda(pos.row + i, pos.col + i)) ||
            _check(make_lambda(pos.row - i, pos.col + i));
    }
}
