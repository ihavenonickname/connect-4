#include <vector>

#include <catch2/catch.hpp>

#include "Game.hpp"

std::function<void (connect_four::CellFallThroughEventData)> create_handler(std::vector<connect_four::CellFallThroughEventData>* memo)
{
    return [memo](connect_four::CellFallThroughEventData event_data) mutable
    {
        memo->push_back(event_data);
    };
}

SCENARIO("On cell fall through event")
{
    GIVEN("An empty 6-row-per-7-column board")
    {
        connect_four::Game game(6, 7, connect_four::Player::PLAYER_1);

        std::vector<connect_four::CellFallThroughEventData> memo;

        game.on_event(create_handler(&memo));

        WHEN("The player chooses the first column")
        {
            auto play_result = game.play(0);

            THEN("The game emits the event 6 times")
            {
                REQUIRE(6 == memo.size());
            }
        }
    }
}
