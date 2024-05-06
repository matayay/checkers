/**
AUTHOR: Matayay Karuna
Project: Checkers
File: piecefactory.cpp
Description: Flyweight factory for creating pieces.
**/

#include "piecefactory.h"

#include "SilverPiece.h"
#include "GoldPiece.h"
#include "SilverKing.h"
#include "GoldKing.h"
#include "Empty.h"
#include "Error.h"

std::unordered_map<PieceType, std::shared_ptr<Piece>> PieceFactory::pieceCache_;

std::shared_ptr<Piece> PieceFactory::createPiece(PieceType type) {
    auto it = pieceCache_.find(type);
    if (it != pieceCache_.end()) {
        return it->second;
    }

    std::shared_ptr<Piece> piece;
    switch (type) {
    case PieceType::Silver:
        piece = std::make_shared<SilverPiece>();
        break;
    case PieceType::Gold:
        piece = std::make_shared<GoldPiece>();
        break;
    case PieceType::SilverKing:
        piece = std::make_shared<SilverKing>();
        break;
    case PieceType::GoldKing:
        piece = std::make_shared<GoldKing>();
        break;
    case PieceType::Empty:
        piece = std::make_shared<Empty>();
        break;
    case PieceType::Error:
        piece = std::make_shared<Error>();
        break;
    }

    if (piece) {
        pieceCache_[type] = piece;
    }

    return piece;
}
