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
    class CellFallThroughEventData;
    class WinEventData;

    class Game
    {
        Player _player;
        Board _board;
        bool _ended;
        std::vector<std::function<void (CellFallThroughEventData)>> _cell_fall_through_handlers;
        std::vector<std::function<void (WinEventData)>> _win_handlers;

        bool _check_victory(Position position);

        public:

        Game(uint_least8_t row_count, uint_least8_t col_count);

        PlayResult play(uint_least8_t col);
        void on_event(std::function<void (CellFallThroughEventData)> handler);
        void on_event(std::function<void (WinEventData)> handler);
    };
}
