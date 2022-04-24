namespace ConnectFour;

public class Board
{
    private readonly int _rowCount;
    private readonly int _colCount;
    private List<Player?> _cells;

    public Board(int rowCount, int colCount)
    {
        _rowCount = rowCount;
        _colCount = colCount;
        _cells = new List<Player?>(_rowCount * _colCount);
    }


}
