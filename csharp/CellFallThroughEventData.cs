namespace ConnectFour;

public record CellFallThroughEventData(
    Player Player,
    int Row,
    int Col,
    bool IsFinalPosition);
