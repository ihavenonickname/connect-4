#include <cstdlib>
#include <iostream>
#include <sstream>

#include "src/Game.hpp"

int GLOBAL_final_positions;
int GLOBAL_player_1_wins;

void on_CellFallThroughEventData(connect_four::CellFallThroughEventData event_data)
{
    if (event_data.is_final_position)
    {
        GLOBAL_final_positions += 1;
    }
}

void on_WinEventData(connect_four::WinEventData event_data)
{
    if (event_data.winner == connect_four::Player::PLAYER_1)
    {
        GLOBAL_player_1_wins += 1;
    }
}

int main(int argc, char **argv)
{
    int n_games;
    int n_rows;
    int n_cols;

    std::istringstream(argv[1]) >> n_games;
    std::istringstream(argv[2]) >> n_rows;
    std::istringstream(argv[3]) >> n_cols;

    int games_ok = 0;

    for (int i = 0; i < n_games; i += 1)
    {
        GLOBAL_final_positions = 0;
        GLOBAL_player_1_wins = 0;

        connect_four::Game game(n_rows, n_cols);

        game.on_event(on_CellFallThroughEventData);
        game.on_event(on_WinEventData);

        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);

        game.play(1);
        game.play(1);
        game.play(1);
        game.play(1);
        game.play(1);
        game.play(1);

        game.play(2);
        game.play(2);
        game.play(2);
        game.play(2);
        game.play(2);
        game.play(2);

        game.play(4);
        game.play(4);
        game.play(4);
        game.play(4);
        game.play(4);
        game.play(4);

        game.play(5);
        game.play(5);
        game.play(5);
        game.play(5);
        game.play(5);
        game.play(5);

        game.play(6);
        game.play(6);
        game.play(6);
        game.play(6);
        game.play(6);
        game.play(6);

        game.play(3);

        if (GLOBAL_final_positions != 37)
        {
            return EXIT_FAILURE;
        }

        if (GLOBAL_player_1_wins != 1)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
