#pragma once

#include <cstdint>
#include <functional>

#include "Board.hpp"
#include "Player.hpp"
#include "PlayResult.hpp"
#include "Position.hpp"

namespace connect_four
{
    using CellFallThroughHandler = std::function<void (Player player, uint_least8_t row, uint_least8_t col, bool is_final_position)>;
    using GameEndHandler = std::function<void (Player winner)>;

    class Game
    {
        Player _player;
        Board _board;
        bool _ended;
        std::vector<CellFallThroughHandler> _cell_fall_through_handlers;
        std::vector<GameEndHandler> _game_ended_handlers;

        Position _fall_to_right_cell(Position position);
        bool _check_victory(Position position);

        public:

        Game(uint_least8_t row_count, uint_least8_t col_count, Player starting);

        PlayResult play(uint_least8_t col);
        void on_event(CellFallThroughHandler handler);
        void on_event(GameEndHandler handler);
    };
}
