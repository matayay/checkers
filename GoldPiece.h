/**
AUTHOR: Matayay Karuna
Project: Checkers
File: GoldPiece.h
Description: Subclass of Piece. Represents a gold piece.
**/

#ifndef GOLDPIECE_H
#define GOLDPIECE_H

#include "Piece.h"

class GoldPiece : public Piece {
public:
    GoldPiece() : Piece(PieceType::Gold) {}
    bool isKing() const override { return false; }
};

#endif // GOLDPIECE_H
