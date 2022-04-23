#pragma once

#include <cstdint>
#include <functional>

#include "Board.hpp"
#include "CellFallThroughEventData.hpp"
#include "WinEventData.hpp"
#include "Player.hpp"
#include "PlayResult.hpp"
#include "Position.hpp"

namespace connect_four
{
    class Game
    {
        Player _player;
        Board _board;
        bool _ended;
        std::function<void (CellFallThroughEventData)> _cell_fall_through_handler;
        std::function<void (WinEventData)> _win_handler;

        bool _check_victory(Position position);
        Position _fall_to_right_row(Position current_position);

        public:

        Game(uint_least8_t const row_count, uint_least8_t const col_count);

        PlayResult play(uint_least8_t const col);
        void on_event(std::function<void (CellFallThroughEventData)> const handler);
        void on_event(std::function<void (WinEventData)> const handler);
    };
}
