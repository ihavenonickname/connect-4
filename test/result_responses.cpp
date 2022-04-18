#include <catch2/catch.hpp>

#include "Game.hpp"

SCENARIO("Result responses")
{
    GIVEN("An empty board")
    {
        connect_four::Game game(6, 7, connect_four::Player::PLAYER_1);

        WHEN("The player chooses the first column")
        {
            auto play_result = game.play(0);

            THEN("The game accepts the play")
            {
                REQUIRE(connect_four::PlayResult::SUCCESS == play_result);
            }
        }
    }

    GIVEN("A board whose first column is full")
    {
        connect_four::Game game(6, 7, connect_four::Player::PLAYER_1);

        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);
        game.play(0);

        WHEN("The player chooses the first column")
        {
            auto play_result = game.play(0);

            THEN("The game does not accept the play")
            {
                REQUIRE(connect_four::PlayResult::COLUMN_IS_FULL == play_result);
            }
        }
    }

    GIVEN("A 6-row-per-7-column board")
    {
        connect_four::Game game(6, 7, connect_four::Player::PLAYER_1);

        WHEN("The player chooses the 8th column")
        {
            auto play_result = game.play(7);

            THEN("The game does not accept the play")
            {
                REQUIRE(connect_four::PlayResult::COLUMN_IS_INVALID == play_result);
            }
        }
    }
}
