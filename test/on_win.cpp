#include <vector>

#include <catch2/catch.hpp>

#include "Game.hpp"

#include "helper.hpp"

using namespace connect_four;

SCENARIO("Win event not emited on normal, non-winning play")
{
    GIVEN("An empty 6-row-per-7-column board")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

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

SCENARIO("Win event emited on horizontal win")
{
    //
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 :   :   :   :   :   :   :   :
    // 4 :   :   :   :   :   :   :   :
    // 5 : O : O : O :   :   :   :   :
    // 6 : X : X : X :   :   :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 112233")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

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
                REQUIRE(Player::PLAYER_1 == memo[0].winner);
            }
        }
    }
}

SCENARIO("Win event emited on vertical win")
{
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 :   :   :   :   :   :   :   :
    // 4 : X : O :   :   :   :   :   :
    // 5 : X : O :   :   :   :   :   :
    // 6 : X : O :   :   :   :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 121212")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

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
                REQUIRE(Player::PLAYER_1 == memo[0].winner);
            }
        }
    }
}

SCENARIO("Win event emited on main diagonal win")
{
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 : X :   :   :   :   :   :   :
    // 4 : O :   : O :   :   :   :   :
    // 5 : O : O : X :   :   :   :   :
    // 6 : X : X : O : X :   :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 1121124333")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

        game.play(0);
        game.play(0);
        game.play(1);
        game.play(0);
        game.play(0);
        game.play(1);
        game.play(3);
        game.play(2);
        game.play(2);
        game.play(2);

        WHEN("The player chooses the 2nd column")
        {
            game.play(1);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner);
            }
        }
    }
}

SCENARIO("Win event emited on secondary diagonal win")
{
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 :   :   : O :   :   :   :   :
    // 4 :   :   : X : O :   :   :   :
    // 5 :   : X : X : O :   :   :   :
    // 6 : X : O : X : O :   :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 1234243433")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

        game.play(0);
        game.play(1);
        game.play(2);
        game.play(3);
        game.play(1);
        game.play(3);
        game.play(2);
        game.play(3);
        game.play(2);
        game.play(2);

        WHEN("The player chooses the 4th column")
        {
            game.play(3);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner);
            }
        }
    }
}

SCENARIO("Win event emited on win when last play at the middle")
{
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 :   :   :   :   :   :   :   :
    // 4 :   :   :   :   :   :   :   :
    // 5 : O : O :   : O : O :   :   :
    // 6 : X : X :   : X : X :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 11224455")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

        game.play(0);
        game.play(0);
        game.play(1);
        game.play(1);
        game.play(3);
        game.play(3);
        game.play(4);
        game.play(4);

        WHEN("The player chooses the 3rd column")
        {
            game.play(2);

            THEN("1 event is emited for player 1")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_1 == memo[0].winner);
            }
        }
    }
}

SCENARIO("Win event emited on player 2 win")
{
    //   : 1 : 2 : 3 : 4 : 5 : 6 : 7 :
    //   :---:---:---:---:---:---:---:
    // 1 :   :   :   :   :   :   :   :
    // 2 :   :   :   :   :   :   :   :
    // 3 :   :   :   :   :   :   :   :
    // 4 :   :   :   :   :   :   :   :
    // 5 : X : X : X :   :   :   :   :
    // 6 : O : O : O :   : X :   :   :
    //   :---------------------------:

    GIVEN("A 6-row-per-7-column board with state 5112233")
    {
        Game game(6, 7);

        std::vector<WinEventData> memo;

        game.on_event(create_handler<WinEventData>(&memo));

        game.play(4);
        game.play(0);
        game.play(0);
        game.play(1);
        game.play(1);
        game.play(2);
        game.play(2);

        WHEN("The player chooses the 4th column")
        {
            game.play(3);

            THEN("1 event is emited for player 2")
            {
                REQUIRE(1 == memo.size());
                REQUIRE(Player::PLAYER_2 == memo[0].winner);
            }
        }
    }
}
