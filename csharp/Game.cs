using System.Diagnostics;

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

        var initialPosition = new Position(0, col);

        if (!_board.IsInside(initialPosition))
        {
            return PlayResult.COLUMN_IS_INVALID;
        }

        if (!_board.IsEmpty(initialPosition))
        {
            return PlayResult.COLUMN_IS_FULL;
        }

        var sw = new Stopwatch();

        sw.Start();

        var position = FallToRightRow(initialPosition);

        Durations.FallToRightRow += sw.Elapsed;

        sw.Reset();

        _board.Set(position, _player);

        sw.Start();

        var isVictory = CheckVictory(position);

        Durations.CheckVictory += sw.Elapsed;

        if (isVictory)
        {
            _ended = true;

            OnWin?.Invoke(new WinEventData(_player));
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
        Position nextPos;

        while (true)
        {
            nextPos = position.MoveHorizontally(1);

            var isFinal = !_board.IsEmpty(nextPos);

            OnCellFallThrough?.Invoke(new CellFallThroughEventData(
                Player: _player,
                Row: position.Row,
                Col: position.Col,
                IsFinalPosition: isFinal));

            if (isFinal)
            {
                return position;
            }

            position = nextPos;
        }
    }

    private bool CheckVictory(Position position)
    {
        // Func<Func<int, Position>, bool> check = f =>
        // {
        //     var counter = 1;
        //     var i = 1;

        //     while (_board.IsFilled(f(i), _player))
        //     {
        //         counter += 1;
        //         i += 1;
        //     }

        //     i = -1;

        //     while (_board.IsFilled(f(i), _player))
        //     {
        //         counter += 1;
        //         i -= 1;
        //     }

        //     return counter >= 4;
        // };

        // return
        //     Check(position.MoveVertically) ||
        //     Check(position.MoveHorizontally) ||
        //     Check(position.MovePrimaryDiagonal) ||
        //     Check(position.MoveSecondaryDiagonal);

        return Check(position);
    }

    private bool Check(Func<int, Position> f)
    {
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
    }

    private bool Check(Position position)
    {
        // vertically

        var counter = 1;
        var i = 1;

        while (_board.IsFilled(position.MoveVertically(i), _player))
        {
            counter += 1;
            i += 1;
        }

        i = -1;

        while (_board.IsFilled(position.MoveVertically(i), _player))
        {
            counter += 1;
            i -= 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // horiontally

        counter = 1;
        i = 1;

        while (_board.IsFilled(position.MoveHorizontally(i), _player))
        {
            counter += 1;
            i += 1;
        }

        i = -1;

        while (_board.IsFilled(position.MoveHorizontally(i), _player))
        {
            counter += 1;
            i -= 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // primary diagonal

        counter = 1;
        i = 1;

        while (_board.IsFilled(position.MovePrimaryDiagonal(i), _player))
        {
            counter += 1;
            i += 1;
        }

        i = -1;

        while (_board.IsFilled(position.MovePrimaryDiagonal(i), _player))
        {
            counter += 1;
            i -= 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        // secondary diagonal

        counter = 1;
        i = 1;

        while (_board.IsFilled(position.MoveSecondaryDiagonal(i), _player))
        {
            counter += 1;
            i += 1;
        }

        i = -1;

        while (_board.IsFilled(position.MoveSecondaryDiagonal(i), _player))
        {
            counter += 1;
            i -= 1;
        }

        if (counter >= 4)
        {
            return true;
        }

        return false;
    }

    // public override string ToString()
    // {
    //     return $"{_board}";
    // }
}
