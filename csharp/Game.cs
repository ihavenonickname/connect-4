namespace ConnectFour;

public class Game
{
    private readonly Board _board;
    private Player _player;
    private bool _ended;

    public event Action<CellFallThroughEventData> OnCellFallThrough = default!;
    public event Action<WinEventData> OnWin = default!;

    public Game(int rowCount, int colCount)
    {
        _board = new Board(rowCount, colCount);
        _ended = false;
        _player = Player.PLAYER_1;
    }

    public PlayResult Play(int col)
    {
        if (_ended)
        {
            return PlayResult.GAME_ALREADY_ENDED;
        }

        var initialPosition = new Position
        {
            Col = col,
            Row = 0,
        };

        if (!_board.IsInside(initialPosition))
        {
            return PlayResult.COLUMN_IS_INVALID;
        }

        if (!_board.IsEmpty(initialPosition))
        {
            return PlayResult.COLUMN_IS_FULL;
        }

        var position = FallToRightRow(initialPosition);

        _board.Set(position, _player);

        if (CheckVictory(position))
        {
            _ended = true;

            OnWin?.Invoke(new WinEventData
            {
                Winner = _player,
            });
        }
        else
        {
            _player =
                _player == Player.PLAYER_1
                ? Player.PLAYER_2
                : Player.PLAYER_1;
        }

        return PlayResult.SUCCESS;
    }

    private Position FallToRightRow(Position position)
    {
        var nextPos = new Position
        {
            Row = position.Row + 1,
            Col = position.Col,
        };

        var isFinal = !_board.IsEmpty(nextPos);

        OnCellFallThrough?.Invoke(new CellFallThroughEventData
        {
            Player = _player,
            Row = position.Row,
            Col = position.Col,
            IsFinalPosition = isFinal,
        });

        return
            isFinal
            ? position
            : FallToRightRow(nextPos);
    }

    private bool CheckVictory(Position position)
    {
        Func<int, int, bool> check = (dx, dy) =>
        {
            Func<int, Position> f = i => new Position
            {
                Row = position.Row + dx * i,
                Col = position.Col + dy * i,
            };

            var counter = 1;
            var i = 1;

            while (_board.IsFilled(f(i), _player))
            {
                counter += 1;
                i += 1;
            }

            i = -1;

            while (_board.IsFilled(f(i), _player))
            {
                counter += 1;
                i -= 1;
            }

            return counter >= 4;
        };

        return check(0, 1) || check(1, 0) || check(1, 1) || check(-1, 1);
    }

    public override string ToString()
    {
        return $"{_board}";
    }
}
