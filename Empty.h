/**
AUTHOR: Matayay Karuna
Project: Checkers
File: Empty.h
Description: Subclass of Piece. Represents an empty square on the board.
**/

#ifndef EMPTY_H
#define EMPTY_H

#include "Piece.h"

class Empty : public Piece {
public:
    Empty() : Piece(PieceType::Empty) {}
    bool isKing() const override { return false; }
};

#endif // EMPTY_H
