#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QWidget>

enum class PieceType
{
    Empty,
    Silver,
    Gold,
    SilverKing,
    GoldKing,
    Error
};

struct Move
{
    std::pair<int, int> start;
    std::pair<int, int> end;
    std::vector<std::pair<int, int>> kills;
};

class Board
{
public:
    // Constructor
    Board();

    // Getters
    PieceType get_piece(int row, int col) const
    {
        if (row < 0 || row > 7 || col < 0 || col > 7)
        {
            return PieceType::Error;
        }

        return board_[row][col];
    }

    PieceType get_turn() const {return turn_;}
    int get_gold_pieces() const {return gold_pieces_;}
    int get_silver_pieces() const {return silver_pieces_;}

    // Setters
    void set_piece(int row, int col, PieceType piece)
    {
        if (row < 0 || row > 7 || col < 0 || col > 7)
        {
            return;
        }

        board_[row][col] = piece;
    }

    void set_turn(PieceType turn) {turn_ = turn;}
    void set_gold_pieces(int gold_pieces) {gold_pieces_ = gold_pieces;}
    void set_silver_pieces(int silver_pieces) {silver_pieces_ = silver_pieces;}

    // Methods
    std::vector<Move> getPossibleMoves(int row, int col);
    std::string getWinner();

    bool isAttackMove(int row, int col, int newRow, int newCol);
    bool isValidMove(int row, int col, int newRow, int newCol);
    bool canMove(int row, int col);
    bool isKing(int row, int col);

    void makeMove(int row, int col, int newRow, int newCol);
    void flipBoard();
    // void resetBoard();

    // Helpers
    std::vector<Move> _movesHelper(int firstRow, int firstCol, int row, int col, bool king, PieceType enemy, PieceType enemyKing, std::vector<Move> &moves);

private:
    PieceType board_[8][8];
    PieceType turn_;

    std::vector<std::pair<int, int>> gold_tiles_;
    std::vector<std::pair<int, int>> silver_tiles_;

    int gold_pieces_;
    int silver_pieces_;
};

#endif // BOARD_H
