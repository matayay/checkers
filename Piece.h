/**
AUTHOR: Matayay Karuna
Project: Checkers
File: Piece.h
Description: Base class for all pieces on the board.
**/

#ifndef PIECE_H
#define PIECE_H

enum class PieceType {
    Empty,
    Silver,
    Gold,
    SilverKing,
    GoldKing,
    Error
};

class Piece
{
public:
    Piece(PieceType type) : type_(type) {}
    virtual ~Piece() {}

    PieceType getType() const { return type_; }
    virtual bool isKing() const = 0;

    int getRow() const { return row_; }
    int getCol() const { return col_; }
    void setRow(int row) { row_ = row; }
    void setCol(int col) { col_ = col; }

protected:
    PieceType type_;
    int row_;
    int col_;
};

#endif // PIECE_H
