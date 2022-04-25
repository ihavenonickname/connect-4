namespace ConnectFour;

public class Board
{
    private readonly int _rowCount;
    private readonly int _colCount;
    private Player?[] _cells;

    public Board(int rowCount, int colCount)
    {
        _rowCount = rowCount;
        _colCount = colCount;
        _cells = new Player?[_rowCount * _colCount];
    }

    public bool IsInside(Position position)
    {
        return
            position.Row >= 0 &&
            position.Col >= 0 &&
            position.Row < _rowCount &&
            position.Col < _colCount;
    }

    public bool IsEmpty(Position position)
    {
        return IsInside(position) && !_cells[Index(position)].HasValue;
    }

    public bool IsFilled(Position position, Player player)
    {
        return IsInside(position) && _cells[Index(position)] == player;
    }

    public void Set(Position position, Player player)
    {
        _cells[Index(position)] = player;
    }

    private int Index(Position position)
    {
        return position.Row * _colCount + position.Col;
    }

    // public override string ToString()
    // {
    //     var s = "";

    //     for (var row = 0; row < _rowCount; row += 1)
    //     {
    //         for (var col = 0; col < _colCount; col += 1)
    //         {
    //             var idx = row * _colCount + col;
    //             switch (_cells[row * _colCount + col])
    //             {
    //                 case Player.PLAYER_1:
    //                 s += "X  ";
    //                 break;
    //                 case Player.PLAYER_2:
    //                 s += "O  ";
    //                 break;
    //                 default:
    //                 s += $"{idx}  ";
    //                 break;
    //             }
    //         }

    //         s += "\n";
    //     }

    //     return s;
    // }
}
