/**
AUTHOR: Matayay Karuna
Project: Checkers
File: piecefactory.h
Description: Flyweight factory definition.
**/

#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <QObject>
#include <QWidget>
#include "Piece.h"

class PieceFactory {
public:
    static std::shared_ptr<Piece> createPiece(PieceType type);
private:
    static std::unordered_map<PieceType, std::shared_ptr<Piece>> pieceCache_;
};

#endif // PIECEFACTORY_H
