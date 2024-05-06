/**
AUTHOR: Matayay Karuna
Project: Checkers
File: SilverKing.h
Description: Subclass of Piece. Represents a silver king piece.
**/

#ifndef SILVERKING_H
#define SILVERKING_H

#include "Piece.h"

class SilverKing : public Piece {
public:
    SilverKing() : Piece(PieceType::SilverKing) {}
    bool isKing() const override { return true; }
};

#endif // SILVERKING_H
