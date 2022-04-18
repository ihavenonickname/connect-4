#include <vector>

#include <catch2/catch.hpp>

#include "Game.hpp"

struct EventData
{
    connect_four::Player player;
    uint8_t row;
    uint8_t col;
    bool is_final_position;
};

connect_four::CellFallThroughHandler create_handler(std::vector<EventData>* memo)
{
    return [memo](connect_four::Player player, uint8_t row, uint8_t col, bool is_final_position) mutable
    {
        memo->push_back({player, row, col, is_final_position});
    };
}

SCENARIO("On cell fall through event")
{
    GIVEN("An empty 6-row-per-7-column board")
    {
        connect_four::Game game(6, 7, connect_four::Player::PLAYER_1);

        std::vector<EventData> memo;

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
