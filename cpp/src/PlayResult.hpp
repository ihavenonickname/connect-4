#pragma once

namespace connect_four
{
    enum class PlayResult
    {
        SUCCESS,
        GAME_ALREADY_ENDED,
        COLUMN_IS_FULL,
        COLUMN_IS_INVALID,
    };
}
