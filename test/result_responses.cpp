#include <catch2/catch.hpp>

#include "Game.hpp"

using namespace connect_four;

SCENARIO("Play happy path")
{
    GIVEN("An empty board")
    {
        Game game(6, 7, Player::PLAYER_1);

        WHEN("The player chooses the first column")
        {
            auto play_result = game.play(0);

            THEN("The game accepts the play")
            {
                REQUIRE(PlayResult::SUCCESS == play_result);
            }
        }
    }
}

SCENARIO("A column that is full cannot accept any more plays")
{
    GIVEN("A board whose first column is full")
    {
        Game game(6, 7, Player::PLAYER_1);

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
                REQUIRE(PlayResult::COLUMN_IS_FULL == play_result);
            }
        }
    }
}

SCENARIO("The chosen column must be validated")
{
    GIVEN("A 6-row-per-7-column board")
    {
        Game game(6, 7, Player::PLAYER_1);

        WHEN("The player chooses the 8th column")
        {
            auto play_result = game.play(7);

            THEN("The game does not accept the play")
            {
                REQUIRE(PlayResult::COLUMN_IS_INVALID == play_result);
            }
        }
    }
}
