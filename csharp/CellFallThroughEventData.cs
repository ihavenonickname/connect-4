namespace ConnectFour;

public class CellFallThroughEventData
{
    public readonly Player Player { get; set; }
    public readonly int Row { get; set; }
    public readonly int Col { get; set; }
    public readonly bool IsFinalPosition { get; set; }
}
