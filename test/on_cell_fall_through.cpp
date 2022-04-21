#include <vector>

#include <catch2/catch.hpp>

#include "Game.hpp"

#include "helper.hpp"

using namespace connect_four;

SCENARIO("Cell fall through event happy path")
{
    GIVEN("An empty 6-row-per-7-column board")
    {
        Game game(6, 7, Player::PLAYER_1);

        std::vector<CellFallThroughEventData> memo;

        game.on_event(create_handler<CellFallThroughEventData>(&memo));

        WHEN("The player chooses a valid column")
        {
            auto column = 4;

            game.play(column);

            THEN("6 events are emited")
            {
                REQUIRE(6 == memo.size());
            }

            THEN("All events report the chosen column")
            {
                for (auto event : memo)
                {
                    REQUIRE(column == event.col());
                }
            }

            THEN("All events report the 1st player")
            {
                for (auto event : memo)
                {
                    REQUIRE(Player::PLAYER_1 == event.player());
                }
            }

            THEN("The 1st event reports the 1st row")
            {
                REQUIRE(0 == memo[0].row());
            }

            THEN("The 6th event reports the 6th row")
            {
                REQUIRE(5 == memo[5].row());
            }

            THEN("The 6th event is reported as final position")
            {
                REQUIRE(true == memo[5].is_final_position());
            }

            THEN("The 1st event is not reported as final position")
            {
                REQUIRE(false == memo[0].is_final_position());
            }
        }
    }
}
