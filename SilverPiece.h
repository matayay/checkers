/**
AUTHOR: Matayay Karuna
Project: Checkers
File: SilverPiece.h
Description: Subclass of Piece. Represents a silver piece.
**/

#ifndef SILVERPIECE_H
#define SILVERPIECE_H

#include "Piece.h"

class SilverPiece : public Piece {
public:
    SilverPiece() : Piece(PieceType::Silver) {}
    bool isKing() const override { return false; }
};

#endif // SILVERPIECE_H
