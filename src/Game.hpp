#pragma once

#include <cstdint>
#include <functional>

#include "Board.hpp"
#include "CellFallThroughEventData.hpp"
#include "GameEndEventData.hpp"
#include "Player.hpp"
#include "PlayResult.hpp"
#include "Position.hpp"

namespace connect_four
{
    class CellFallThroughEventData;
    class GameEndEventData;

    class Game
    {
        Player _player;
        Board _board;
        bool _ended;
        std::vector<std::function<void (CellFallThroughEventData)>> _cell_fall_through_handlers;
        std::vector<std::function<void (GameEndEventData)>> _game_end_handlers;

        bool _check_victory(Position position);

        public:

        Game(uint_least8_t row_count, uint_least8_t col_count, Player starting);

        PlayResult play(uint_least8_t col);
        void on_event(std::function<void (CellFallThroughEventData)> handler);
        void on_event(std::function<void (GameEndEventData)> handler);
    };
}
