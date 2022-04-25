namespace ConnectFour;

public record Position(int Row, int Col)
{
    public Position MoveHorizontally(int offset)
    {
        return new Position(Row + offset, Col);
    }

    public Position MoveVertically(int offset)
    {
        return new Position(Row, Col + offset);
    }

    public Position MovePrimaryDiagonal(int offset)
    {
        return new Position(Row + offset, Col + offset);
    }

    public Position MoveSecondaryDiagonal(int offset)
    {
        return new Position(Row - offset, Col + offset);
    }
}
