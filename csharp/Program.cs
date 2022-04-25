// See https://aka.ms/new-console-template for more information
using System.Diagnostics;
using ConnectFour;

int GLOBAL_final_positions;
int GLOBAL_player_1_wins;

void HandleCellFallThrough(CellFallThroughEventData eventData)
{
    if (eventData.IsFinalPosition)
    {
        GLOBAL_final_positions += 1;
    }
}

void HandleWin(WinEventData eventData)
{
    if (eventData.Winner == Player.PLAYER_1)
    {
        GLOBAL_player_1_wins += 1;
    }
}

int nGames = int.Parse(Environment.GetCommandLineArgs()[1]);
int nRows = int.Parse(Environment.GetCommandLineArgs()[2]);
int nCols = int.Parse(Environment.GetCommandLineArgs()[3]);

// int nGames = 1;
// int nRows = 6;
// int nCols = 6;

void Run()
{
    GLOBAL_final_positions = 0;
    GLOBAL_player_1_wins = 0;

    var game = new Game(nRows, nCols);

    game.OnCellFallThrough += HandleCellFallThrough;
    game.OnWin += HandleWin;

    game.Play(0);
    game.Play(0);
    game.Play(0);
    game.Play(0);
    game.Play(0);
    game.Play(0);

    game.Play(1);
    game.Play(1);
    game.Play(1);
    game.Play(1);
    game.Play(1);
    game.Play(1);

    game.Play(2);
    game.Play(2);
    game.Play(2);
    game.Play(2);
    game.Play(2);
    game.Play(2);

    game.Play(4);
    game.Play(4);
    game.Play(4);
    game.Play(4);
    game.Play(4);
    game.Play(4);

    game.Play(5);
    game.Play(5);
    game.Play(5);
    game.Play(5);
    game.Play(5);
    game.Play(5);

    game.Play(6);
    game.Play(6);
    game.Play(6);
    game.Play(6);
    game.Play(6);
    game.Play(6);

    game.Play(3);
}

Run();

Durations.FallToRightRow = TimeSpan.Zero;
Durations.CheckVictory = TimeSpan.Zero;

var sw = new Stopwatch();

sw.Start();

for (var i = 0; i < nGames; i += 1)
{
    Run();

    if (GLOBAL_final_positions != 37)
    {
        throw new Exception("oopsie 1");
    }

    if (GLOBAL_player_1_wins != 1)
    {
        throw new Exception("oopsie 2");
    }
}

Console.WriteLine($"Program: {sw.Elapsed}");
Console.WriteLine($"FallToRightRow: {Durations.FallToRightRow}");
Console.WriteLine($"CheckVictory: {Durations.CheckVictory}");

public static class Durations
{
    public static TimeSpan CheckVictory = TimeSpan.Zero;
    public static TimeSpan FallToRightRow = TimeSpan.Zero;
}
