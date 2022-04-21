#include <vector>

#include <catch2/catch.hpp>

#include "Game.hpp"

#include "helper.hpp"

using namespace connect_four;

SCENARIO("End game event not emited on normal, non-winning play")
{
    GIVEN("An empty 6-row-per-7-column board")
    {
        Game game(6, 7, Player::PLAYER_1);

        std::vector<GameEndEventData> memo;

        game.on_event(create_handler<GameEndEventData>(&memo));

        WHEN("The player chooses a valid column")
        {
            game.play(0);

            THEN("No event is emited")
            {
                REQUIRE(0 == memo.size());
            }
        }
    }
}

SCENARIO("End game event emited on horizontal win")
{
    GIVEN("A 6-row-per-7-column board with plays 112233")
    {
        Game game(6, 7, Player::PLAYER_1);

        std::vector<GameEndEventData> memo;

        game.on_event(create_handler<GameEndEventData>(&memo));

        game.play(0);
        game.play(0);
        game.play(1);
        game.play(1);
        game.play(2);
        game.play(2);

        WHEN("The player chooses the 4th column")
        {
            game.play(3);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner());
            }
        }
    }
}

SCENARIO("End game event emited on vertical win")
{
    GIVEN("A 6-row-per-7-column board with plays 121212")
    {
        Game game(6, 7, Player::PLAYER_1);

        std::vector<GameEndEventData> memo;

        game.on_event(create_handler<GameEndEventData>(&memo));

        game.play(0);
        game.play(1);
        game.play(0);
        game.play(1);
        game.play(0);
        game.play(1);

        WHEN("The player chooses the 1th column")
        {
            game.play(0);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner());
            }
        }
    }
}

// SCENARIO("End game event emited on main diagonal win")
// {
//     GIVEN("A 6-row-per-7-column board with plays 12334455552")
//     {
//         Game game(6, 7, Player::PLAYER_1);

//         std::vector<GameEndEventData> memo;

//         game.on_event(create_handler<GameEndEventData>(&memo));

//         game.play(0);
//         game.play(1);
//         game.play(2);
//         game.play(2);
//         game.play(3);
//         game.play(3);
//         game.play(4);
//         game.play(4);
//         game.play(4);
//         game.play(4);
//         game.play(1);

//         WHEN("The player chooses the 3th column")
//         {
//             game.play(2);

//             THEN("1 event is emited for player 1")
//             {
//                 REQUIRE(1 == memo.size());
//                 REQUIRE(Player::PLAYER_1 == memo[0].winner());
//             }
//         }
//     }
// }

SCENARIO("End game event emited on win when last play at the middle")
{
    GIVEN("A 6-row-per-7-column board with plays 11224455")
    {
        Game game(6, 7, Player::PLAYER_1);

        std::vector<GameEndEventData> memo;

        game.on_event(create_handler<GameEndEventData>(&memo));

        game.play(0);
        game.play(0);
        game.play(1);
        game.play(1);
        game.play(3);
        game.play(3);
        game.play(4);
        game.play(4);

        WHEN("The player chooses the 3th column")
        {
            game.play(2);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner());
            }
        }
    }
}

// SCENARIO("End game event emited on player 2 win")
// {
//     GIVEN("A 6-row-per-7-column board with plays 1122335")
//     {
//         Game game(6, 7, Player::PLAYER_1);

//         std::vector<GameEndEventData> memo;

//         game.on_event(create_handler<GameEndEventData>(&memo));

//         game.play(0);
//         game.play(0);
//         game.play(1);
//         game.play(1);
//         game.play(2);
//         game.play(2);
//         game.play(4);

//         WHEN("The player chooses the 4th column")
//         {
//             game.play(3);

//             THEN("1 event is emited for player 2")
//             {
//                 REQUIRE(1 == memo.size());
//                 REQUIRE(Player::PLAYER_2 == memo[0].winner());
//             }
//         }
//     }
// }
