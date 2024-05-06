/**
AUTHOR: Matayay Karuna
Project: Checkers
File: GoldKing.h
Description: Subclass of Piece. Represents a gold king piece.
**/

#ifndef GOLDKING_H
#define GOLDKING_H

#include "Piece.h"

class GoldKing : public Piece {
public:
    GoldKing() : Piece(PieceType::GoldKing) {}
    bool isKing() const override { return true; }
};

#endif // GOLDKING_H
