/**
AUTHOR: Matayay Karuna
Project: Checkers
File: Error.h
Description: Subclass of Piece. Represents a value off of the board.
**/

#ifndef ERROR_H
#define ERROR_H

#include "Piece.h"

class Error : public Piece {
public:
    Error() : Piece(PieceType::Error) {}
    bool isKing() const override { return false; }
};

#endif // ERROR_H
