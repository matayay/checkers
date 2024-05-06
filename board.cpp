#include "board.h"

Board::Board()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if ((row + col) % 2 == 0)
            {
                if (row < 3)
                {
                    board_[row][col] = PieceType::Silver;
                    silver_tiles_.push_back(std::make_pair(row, col));
                }
                else if (row > 4)
                {
                    board_[row][col] = PieceType::Gold;
                    gold_tiles_.push_back(std::make_pair(row, col));
                }
                else
                {
                    board_[row][col] = PieceType::Empty;
                }
            }

            else
            {
                board_[row][col] = PieceType::Empty;
            }
        }
    }

    turn_ = PieceType::Gold;
    gold_pieces_ = 12;
    silver_pieces_ = 12;
}


std::vector<Move> Board::getPossibleMoves(int row, int col)
{
    std::vector<Move> possible_moves;

    if (get_piece(row, col) == PieceType::Empty)
    {
        return possible_moves;
    }

    if (isKing(row, col))
    {
        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row, col) == PieceType::GoldKing)
            {
                if (get_piece(row - 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row - 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row + 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row + 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                return _movesHelper(row, col, row, col, true, PieceType::Silver, PieceType::SilverKing, possible_moves);
            }

            return possible_moves;
        }
        else
        {
            if (get_piece(row, col) == PieceType::SilverKing)
            {
                if (get_piece(row - 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row - 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row + 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row + 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                return _movesHelper(row, col, row, col, true, PieceType::Gold, PieceType::GoldKing, possible_moves);
            }

            return possible_moves;
        }
    }

    else
    {
        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row, col) == PieceType::Gold)
            {
                if (get_piece(row - 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row - 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row - 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                return _movesHelper(row, col, row, col, false, PieceType::Silver, PieceType::SilverKing, possible_moves);
            }

            return possible_moves;
        }

        else
        {
            if (get_piece(row, col) == PieceType::Silver)
            {
                if (get_piece(row + 1, col - 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col - 1);

                    possible_moves.push_back(new_move);
                }

                if (get_piece(row + 1, col + 1) == PieceType::Empty)
                {
                    Move new_move;
                    new_move.start = std::make_pair(row, col);
                    new_move.end = std::make_pair(row + 1, col + 1);

                    possible_moves.push_back(new_move);
                }

                return _movesHelper(row, col, row, col, false, PieceType::Gold, PieceType::GoldKing, possible_moves);
            }

            return possible_moves;
        }
    }
}


std::string Board::getWinner()
{
    if (gold_pieces_ == 0)
    {
        return "Silver Wins!";
    }

    else if (silver_pieces_ == 0)
    {
        return "Gold Wins!";
    }

    else
    {
        return "Tie!";
    }
}


bool Board::isAttackMove(int row, int col, int newRow, int newCol)
{
    if (newRow != row - 1 && newCol != col - 1 && newRow != row + 1 && newCol != col + 1)
    {
        return true;
    }

    return false;
}


bool Board::isValidMove(int row, int col, int newRow, int newCol)
{
    std::vector<Move> moves = getPossibleMoves(row, col);

    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i].end.first == newRow && moves[i].end.second == newCol)
        {
            return true;
        }
    }

    return false;
}


bool Board::canMove(int row, int col)
{
    if (isKing(row, col))
    {
        if (get_piece(row - 1, col - 1) == PieceType::Empty || get_piece(row - 1, col + 1) == PieceType::Empty || get_piece(row + 1, col - 1) == PieceType::Empty || get_piece(row + 1, col + 1) == PieceType::Empty)
        {
            return true;
        }

        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row - 1, col - 1) == PieceType::Silver || get_piece(row - 1, col - 1) == PieceType::SilverKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row - 1, col + 1) == PieceType::Silver || get_piece(row - 1, col + 1) == PieceType::SilverKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row + 1, col - 1) == PieceType::Silver || get_piece(row + 1, col - 1) == PieceType::SilverKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row + 1, col + 1) == PieceType::Silver || get_piece(row + 1, col + 1) == PieceType::SilverKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            return false;
        }

        else
        {
            if (get_piece(row - 1, col - 1) == PieceType::Gold || get_piece(row - 1, col - 1) == PieceType::GoldKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row - 1, col + 1) == PieceType::Gold || get_piece(row - 1, col + 1) == PieceType::GoldKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row + 1, col - 1) == PieceType::Gold || get_piece(row + 1, col - 1) == PieceType::GoldKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row + 1, col + 1) == PieceType::Gold || get_piece(row + 1, col + 1) == PieceType::GoldKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            return false;
        }
    }

    else
    {
        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row - 1, col - 1) == PieceType::Empty || get_piece(row - 1, col + 1) == PieceType::Empty)
            {
                return true;
            }

            if (get_piece(row - 1, col - 1) == PieceType::Silver || get_piece(row - 1, col - 1) == PieceType::SilverKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row - 1, col + 1) == PieceType::Silver || get_piece(row - 1, col + 1) == PieceType::SilverKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            return false;
        }

        else
        {
            if (get_piece(row + 1, col - 1) == PieceType::Empty || get_piece(row + 1, col + 1) == PieceType::Empty)
            {
                return true;
            }

            if (get_piece(row + 1, col - 1) == PieceType::Gold || get_piece(row + 1, col - 1) == PieceType::GoldKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            if (get_piece(row + 1, col + 1) == PieceType::Gold || get_piece(row + 1, col + 1) == PieceType::GoldKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty)
                {
                    return true;
                }
            }

            return false;
        }
    }
}


bool Board::isKing(int row, int col)
{
    if (get_piece(row, col) == PieceType::GoldKing || get_piece(row, col) == PieceType::SilverKing)
    {
        return true;
    }

    return false;
}


void Board::makeMove(int row, int col, int newRow, int newCol)
{
    std::vector<Move> moves = getPossibleMoves(row, col);
    std::vector<std::pair<int, int>> kills;
    bool valid = false;

    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i].end.first == newRow && moves[i].end.second == newCol)
        {
            kills = moves[i].kills;
            valid = true;
            break;
        }
    }

    if (valid)
    {
        if (isAttackMove(row, col, newRow, newCol))
        {
            for (int i = 0; i < kills.size(); i++)
            {
                board_[kills[i].first][kills[i].second] = PieceType::Empty;

                if (turn_ == PieceType::Gold)
                {
                    silver_pieces_--;
                    silver_tiles_.erase(std::remove(silver_tiles_.begin(), silver_tiles_.end(), std::make_pair(kills[i].first, kills[i].second)), silver_tiles_.end());
                }
                else
                {
                    gold_pieces_--;
                    gold_tiles_.erase(std::remove(gold_tiles_.begin(), gold_tiles_.end(), std::make_pair(kills[i].first, kills[i].second)), gold_tiles_.end());
                }
            }

            if (newRow == 0 && get_piece(row, col) == PieceType::Gold && turn_ == PieceType::Gold)
            {
                set_piece(newRow, newCol, PieceType::GoldKing);
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }

            else if (newRow == 7 && get_piece(row, col) == PieceType::Silver && turn_ == PieceType::Silver)
            {
                set_piece(newRow, newCol, PieceType::SilverKing);
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }

            else
            {
                set_piece(newRow, newCol, get_piece(row, col));
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }
        }

        else
        {
            if (newRow == 0 && get_piece(row, col) == PieceType::Gold && turn_ == PieceType::Gold)
            {
                set_piece(newRow, newCol, PieceType::GoldKing);
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }

            else if (newRow == 7 && get_piece(row, col) == PieceType::Silver && turn_ == PieceType::Silver)
            {
                set_piece(newRow, newCol, PieceType::SilverKing);
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }

            else
            {
                set_piece(newRow, newCol, get_piece(row, col));
                set_piece(row, col, PieceType::Empty);
                flipBoard();
            }
        }
    }
}


void Board::flipBoard()
{
    if (turn_ == PieceType::Gold)
    {
        turn_ = PieceType::Silver;
    }
    else
    {
        turn_ = PieceType::Gold;
    }

    // gold_tiles_.clear();
    // silver_tiles_.clear();

    // std::unordered_map<int, bool> map;
    // std::unordered_map<int, bool> flipped[8];

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         flipped[i][j] = false;
    //     }
    // }

    // for (int row = 0; row < 8; row++)
    // {
    //     for (int col = 0; col < 8; col++)
    //     {
    //         if (!flipped[row][col])
    //         {
    //             if (board_[row][col] == PieceType::Gold || board_[row][col] == PieceType::GoldKing)
    //             {
    //                 PieceType temp = board_[7 - row][7 - col];
    //                 board_[7 - row][7 - col] = board_[row][col];
    //                 board_[row][col] = temp;
    //                 flipped[row][col] = true;
    //                 flipped[7 - row][7 - col] = true;

    //                 gold_tiles_.push_back(std::make_pair(7 - row, 7 - col));

    //                 if (temp == PieceType::Silver || temp == PieceType::SilverKing)
    //                 {
    //                     silver_tiles_.push_back(std::make_pair(row, col));
    //                 }
    //             }

    //             else if (board_[row][col] == PieceType::Silver || board_[row][col] == PieceType::SilverKing)
    //             {
    //                 PieceType temp = board_[7 - row][7 - col];
    //                 board_[7 - row][7 - col] = board_[row][col];
    //                 board_[row][col] = temp;
    //                 flipped[row][col] = true;
    //                 flipped[7 - row][7 - col] = true;

    //                 silver_tiles_.push_back(std::make_pair(7 - row, 7 - col));

    //                 if (temp == PieceType::Gold || temp == PieceType::GoldKing)
    //                 {
    //                     gold_tiles_.push_back(std::make_pair(row, col));
    //                 }
    //             }
    //         }
    //     }
    // }
}


std::vector<Move> Board::_movesHelper(int firstRow, int firstCol, int row, int col, bool king, PieceType enemy, PieceType enemyKing, std::vector<Move> &moves)
{
    if (king)
    {
        std::vector<Move> TLeft = moves;
        std::vector<Move> TRight = moves;
        std::vector<Move> BLeft = moves;
        std::vector<Move> BRight = moves;

        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row - 1, col - 1) == enemy || get_piece(row - 1, col - 1) == enemyKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::GoldKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col - 2);

                    if (TLeft.size() > 0)
                    {
                        int kills = TLeft[TLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TLeft[TLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col - 1));

                    TLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col - 2, king, enemy, enemyKing, TLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row - 1, col + 1) == enemy || get_piece(row - 1, col + 1) == enemyKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::GoldKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col + 2);

                    if (TRight.size() > 0)
                    {
                        int kills = TRight[TRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TRight[TRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col + 1));

                    TRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col + 2, king, enemy, enemyKing, TRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TRight.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row + 1, col - 1) == enemy || get_piece(row + 1, col - 1) == enemyKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::GoldKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col - 2);

                    if (BLeft.size() > 0)
                    {
                        int kills = BLeft[BLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(BLeft[BLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col - 1));

                    BLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col - 2, king, enemy, enemyKing, BLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        BLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row + 1, col + 1) == enemy || get_piece(row + 1, col + 1) == enemyKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::GoldKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col + 2);

                    if (BRight.size() > 0)
                    {
                        int kills = BRight[BRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(BRight[BRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col + 1));

                    BRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col + 2, king, enemy, enemyKing, BRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        BRight.push_back(temp[i]);
                    }
                }
            }
        }
        else
        {
            if (get_piece(row - 1, col - 1) == enemy || get_piece(row - 1, col - 1) == enemyKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::SilverKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col - 2);

                    if (TLeft.size() > 0)
                    {
                        int kills = TLeft[TLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TLeft[TLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col - 1));

                    TLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col - 2, king, enemy, enemyKing, TLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row - 1, col + 1) == enemy || get_piece(row - 1, col + 1) == enemyKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::SilverKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col + 2);

                    if (TRight.size() > 0)
                    {
                        int kills = TRight[TRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TRight[TRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col + 1));

                    TRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col + 2, king, enemy, enemyKing, TRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TRight.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row + 1, col - 1) == enemy || get_piece(row + 1, col - 1) == enemyKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::SilverKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col - 2);

                    if (BLeft.size() > 0)
                    {
                        int kills = BLeft[BLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(BLeft[BLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col - 1));

                    BLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col - 2, king, enemy, enemyKing, BLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        BLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row + 1, col + 1) == enemy || get_piece(row + 1, col + 1) == enemyKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::SilverKing)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col + 2);

                    if (BRight.size() > 0)
                    {
                        int kills = BRight[BRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(BRight[BRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col + 1));

                    BRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col + 2, king, enemy, enemyKing, BRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        BRight.push_back(temp[i]);
                    }
                }
            }
        }

        moves.clear();
        for (int i = 0; i < TLeft.size(); i++)
        {
            moves.push_back(TLeft[i]);
        }
        for (int i = 0; i < TRight.size(); i++)
        {
            moves.push_back(TRight[i]);
        }
        for (int i = 0; i < BLeft.size(); i++)
        {
            moves.push_back(BLeft[i]);
        }
        for (int i = 0; i < BRight.size(); i++)
        {
            moves.push_back(BRight[i]);
        }

        return moves;
    }

    else
    {
        std::vector<Move> TLeft = moves;
        std::vector<Move> TRight = moves;

        if (turn_ == PieceType::Gold)
        {
            if (get_piece(row - 1, col - 1) == enemy || get_piece(row - 1, col - 1) == enemyKing)
            {
                if (get_piece(row - 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::Gold)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col - 2);

                    if (TLeft.size() > 0)
                    {
                        int kills = TLeft[TLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TLeft[TLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col - 1));

                    TLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col - 2, king, enemy, enemyKing, TLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row - 1, col + 1) == enemy || get_piece(row - 1, col + 1) == enemyKing)
            {
                if (get_piece(row - 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::Gold)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row - 2, col + 2);

                    if (TRight.size() > 0)
                    {
                        int kills = TRight[TRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TRight[TRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row - 1, col + 1));

                    TRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row - 2, col + 2, king, enemy, enemyKing, TRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TRight.push_back(temp[i]);
                    }
                }
            }
        }
        else
        {
            if (get_piece(row + 1, col - 1) == enemy || get_piece(row + 1, col - 1) == enemyKing)
            {
                if (get_piece(row + 2, col - 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::Silver)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col - 2);

                    if (TLeft.size() > 0)
                    {
                        int kills = TLeft[TLeft.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TLeft[TLeft.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col - 1));

                    TLeft.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col - 2, king, enemy, enemyKing, TLeft);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TLeft.push_back(temp[i]);
                    }
                }
            }

            if (get_piece(row + 1, col + 1) == enemy || get_piece(row + 1, col + 1) == enemyKing)
            {
                if (get_piece(row + 2, col + 2) == PieceType::Empty && get_piece(firstRow, firstCol) == PieceType::Silver)
                {
                    Move new_move;
                    new_move.start = std::make_pair(firstRow, firstCol);
                    new_move.end = std::make_pair(row + 2, col + 2);

                    if (TRight.size() > 0)
                    {
                        int kills = TRight[TRight.size() - 1].kills.size();
                        for (int i = 0; i < kills; i++)
                        {
                            new_move.kills.push_back(TRight[TRight.size() - 1].kills[i]);
                        }
                    }

                    new_move.kills.push_back(std::make_pair(row + 1, col + 1));

                    TRight.push_back(new_move);
                    std::vector<Move> temp = _movesHelper(firstRow, firstCol, row + 2, col + 2, king, enemy, enemyKing, TRight);

                    for (int i = 0; i < temp.size(); i++)
                    {
                        TRight.push_back(temp[i]);
                    }
                }
            }
        }

        moves.clear();
        for (int i = 0; i < TLeft.size(); i++)
        {
            moves.push_back(TLeft[i]);
        }
        for (int i = 0; i < TRight.size(); i++)
        {
            moves.push_back(TRight[i]);
        }

        return moves;
    }
}
















