namespace ConnectFour;

public struct CellFallThroughEventData
{
    public Player Player { get; init; }
    public int Row { get; init; }
    public int Col { get; init; }
    public bool IsFinalPosition { get; init; }
}
