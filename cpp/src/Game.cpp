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
    Game::Game(uint_least8_t row_count, uint_least8_t col_count):
        _player(Player::PLAYER_1),
        _board(row_count, col_count),
        _ended(false)
    { }

    PlayResult Game::play(uint_least8_t const col)
    {
        if (_ended)
        {
            return PlayResult::GAME_ALREADY_ENDED;
        }

        Position initial_position{0, col};

        if (!_board.is_inside(initial_position))
        {
            return PlayResult::COLUMN_IS_INVALID;
        }

        if (!_board.is_empty(initial_position))
        {
            return PlayResult::COLUMN_IS_FULL;
        }

        auto position = _fall_to_right_row(initial_position);

        _board.set(position, _player);

        if (_check_victory(position))
        {
            _ended = true;

            if (_win_handler)
            {
                _win_handler(WinEventData{_player});
            }
        }
        else
        {
            _player =
                _player == Player::PLAYER_1
                ? Player::PLAYER_2
                : Player::PLAYER_1;
        }

        return PlayResult::SUCCESS;
    }

    void Game::on_event(std::function<void (CellFallThroughEventData)> const handler)
    {
        _cell_fall_through_handler = handler;
    }

    void Game::on_event(std::function<void (WinEventData)> const handler)
    {
        _win_handler = handler;
    }

    Position Game::_fall_to_right_row(Position position)
    {
        Position next_pos{static_cast<int_least16_t>(position.row + 1), position.col};
        auto is_final = !_board.is_empty(next_pos);

        if (_cell_fall_through_handler)
        {
            _cell_fall_through_handler(CellFallThroughEventData{
                _player,
                static_cast<uint_least8_t>(position.row),
                static_cast<uint_least8_t>(position.col),
                is_final
            });
        }

        return
            is_final
            ? position
            : _fall_to_right_row(next_pos);
    }

    bool Game::_check_victory(Position position)
    {
        auto _check = [this, position](int_least16_t dx, int_least16_t dy)
        {
            auto f = [position, dx, dy](int_least16_t i)
            {
                return Position{
                    static_cast<int_least16_t>(position.row + dx * i),
                    static_cast<int_least16_t>(position.col + dy * i)};
            };

            auto counter = 1;
            int_least16_t i = 1;

            while (_board.is_filled(f(i), _player))
            {
                counter += 1;
                i += 1;
            }

            i = -1;

            while (_board.is_filled(f(i), _player))
            {
                counter += 1;
                i -= 1;
            }

            return counter >= 4;
        };

        return _check(0, 1) || _check(1, 0) || _check(1, 1) || _check(-1, 1);
    }
}
