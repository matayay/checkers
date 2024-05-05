#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_board_ = Board();
}


// Methods
void MainWindow::update_board()
{
    // Define the styles for the checker pieces
    QString silver_piece_style = "QWidget { background-color: white; border-radius: 40px; }";
    QString silver_king_style = "QWidget { background-color: white; border-radius: 40px; border: 5px solid red; }";

    QString gold_piece_style = "QWidget { background-color: gold; border-radius: 40px; }";
    QString gold_king_style = "QWidget { background-color: gold; border-radius: 40px; border: 5px solid red; }";

    QString gole_tile_style = "QWidget#tile%1%2 { background-color: #D3BA34; }";
    QString silver_tile_style = "QWidget#tile%1%2 { background-color: #CDD0D4; }";

    int pieceSize = 80;
    int offset = (100 - pieceSize) / 2;

    delete_pieces();
    int count = 0;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
            QWidget *tile = findChild<QWidget *>(tileObjectName);

            if (tile)
            {
                if ((row + col) % 2 == 0)
                {
                    tile->setStyleSheet(gole_tile_style.arg(row).arg(col));
                }

                else
                {
                    tile->setStyleSheet(silver_tile_style.arg(row).arg(col));
                }
            }

            if (game_board_.get_piece(row, col) == PieceType::Gold)
            {
                if (tile)
                {
                    QWidget *gold_piece = new QWidget(tile);
                    gold_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    gold_piece->setStyleSheet(gold_piece_style);

                    QString piece_object_name = QString("p%1").arg(count);
                    gold_piece->setObjectName(piece_object_name);

                    gold_piece->show();
                    gold_pieces_.append(gold_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::GoldKing)
            {
                if (tile)
                {
                    QWidget *gold_piece = new QWidget(tile);
                    gold_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    gold_piece->setStyleSheet(gold_king_style);

                    QString piece_object_name = QString("p%1").arg(count);
                    gold_piece->setObjectName(piece_object_name);

                    gold_piece->show();
                    gold_pieces_.append(gold_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::Silver)
            {
                if (tile)
                {
                    QWidget *silver_piece = new QWidget(tile);
                    silver_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    silver_piece->setStyleSheet(silver_piece_style);

                    QString piece_object_name = QString("p%1").arg(count);
                    silver_piece->setObjectName(piece_object_name);

                    silver_piece->show();
                    silver_pieces_.append(silver_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::SilverKing)
            {
                if (tile)
                {
                    QWidget *silver_piece = new QWidget(tile);
                    silver_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    silver_piece->setStyleSheet(silver_king_style);

                    QString piece_object_name = QString("p%1").arg(count);
                    silver_piece->setObjectName(piece_object_name);

                    silver_piece->show();
                    silver_pieces_.append(silver_piece);
                }
            }

            count++;
        }
    }
}


void MainWindow::end_game()
{
    ui->game_btn->setText("Start Game");

    delete_pieces();

    std::string winner = game_board_.getWinner();
    QWidget *board = findChild<QWidget *>(QString("board"));

    if (board)
    {
        winner_label_ = new QLabel(board);
        winner_label_->setText(QString::fromStdString(winner));
        winner_label_->setGeometry(0, 0, 800, 800);
        winner_label_->setAlignment(Qt::AlignCenter);
        winner_label_->setStyleSheet("font-size: 36px; font-weight: bold; color: green;");
        winner_label_->show();
    }

    game_board_ = Board();
}


void MainWindow::delete_pieces()
{
    // Loop to remove silver checker pieces
    for (auto piece : silver_pieces_) {
        piece->hide();
        delete piece;
    }
    silver_pieces_.clear();

    // Loop to remove gold checker pieces
    for (auto piece : gold_pieces_) {
        piece->hide();
        delete piece;
    }
    gold_pieces_.clear();
}


bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        QWidget* clicked_widget = qobject_cast<QWidget*>(obj);

        if (clicked_widget == ui->board)
        {
            QWidget* child_widget = ui->board->childAt(pos);
            if (child_widget)
            {
                QString object_name = child_widget->objectName();
                QString other_object_name = child_widget->parent()->objectName();

                if (object_name.contains("tile"))
                {
                    handleClickedPiece(object_name);
                    return true;
                }

                else if (other_object_name.contains("tile"))
                {
                    handleClickedPiece(other_object_name);
                    return true;
                }
            }
        }

        return false;
    }

    return false;
}


// Slots
void MainWindow::on_game_btn_clicked()
{
    if (ui->game_btn->text() == "Start Game")
    {
        ui->game_btn->setText("End Game");

        if (winner_label_)
        {
            winner_label_->hide();
            delete winner_label_;
        }

        update_board();
        ui->board->installEventFilter(this);
    }

    else if (ui->game_btn->text() == "End Game")
    {
        end_game();
    }
}


void MainWindow::handleClickedPiece(const QString& objectName)
{
    int row = objectName[4].digitValue();
    int col = objectName[5].digitValue();

    if (selected_piece_)
    {
        if (selected_piece_->first == row && selected_piece_->second == col)
        {
            return;
        }

        if (game_board_.isValidMove(selected_piece_->first, selected_piece_->second, row, col))
        {
            game_board_.makeMove(selected_piece_->first, selected_piece_->second, row, col);
            delete selected_piece_;
            selected_piece_ = nullptr;
            update_board();

            return;
        }
        else
        {
            delete selected_piece_;
            selected_piece_ = nullptr;
            update_board();

            selected_piece_ = new std::pair<int, int>(row, col);

            QWidget* clicked_tile = findChild<QWidget *>(objectName);
            QString stylesheet = clicked_tile->styleSheet();
            int bracketIndex = stylesheet.lastIndexOf('}');
            stylesheet.insert(bracketIndex, "border: 3px solid blue;");
            clicked_tile->setStyleSheet(stylesheet);

            std::vector<Move> moves = game_board_.getPossibleMoves(row, col);

            QVector<QWidget*> move_tiles;
            for (int i = 0; i < moves.size(); i++)
            {
                Move move = moves[i];
                std::pair<int, int> end = move.end;
                QString tileObjectName = QString("tile%1%2").arg(end.first).arg(end.second);
                QWidget* tile = findChild<QWidget *>(tileObjectName);

                if (tile)
                {
                    move_tiles.append(tile);
                }
            }

            for (int i = 0; i < move_tiles.size(); i++)
            {
                QString stylesheet = move_tiles[i]->styleSheet();
                int bracketIndex = stylesheet.lastIndexOf('}');

                Move move = moves[i];
                std::pair<int, int> end = move.end;
                if (game_board_.isAttackMove(row, col, end.first, end.second))
                {
                    stylesheet.insert(bracketIndex, "border: 3px solid red;");
                }
                else
                {
                    stylesheet.insert(bracketIndex, "border: 3px solid green;");
                }

                move_tiles[i]->setStyleSheet(stylesheet);
            }

            return;
        }
    }

    else
    {
        selected_piece_ = new std::pair<int, int>(row, col);

        QWidget* clicked_tile = findChild<QWidget *>(objectName);
        QString stylesheet = clicked_tile->styleSheet();
        int bracketIndex = stylesheet.lastIndexOf('}');
        stylesheet.insert(bracketIndex, "border: 3px solid blue;");
        clicked_tile->setStyleSheet(stylesheet);

        std::vector<Move> moves = game_board_.getPossibleMoves(row, col);

        QVector<QWidget*> move_tiles;
        for (int i = 0; i < moves.size(); i++)
        {
            Move move = moves[i];
            std::pair<int, int> end = move.end;
            QString tileObjectName = QString("tile%1%2").arg(end.first).arg(end.second);
            QWidget* tile = findChild<QWidget *>(tileObjectName);

            if (tile)
            {
                move_tiles.append(tile);
            }
        }

        for (int i = 0; i < move_tiles.size(); i++)
        {
            QString stylesheet = move_tiles[i]->styleSheet();
            int bracketIndex = stylesheet.lastIndexOf('}');

            Move move = moves[i];
            std::pair<int, int> end = move.end;
            if (game_board_.isAttackMove(row, col, end.first, end.second))
            {
                stylesheet.insert(bracketIndex, "border: 3px solid red;");
            }
            else
            {
                stylesheet.insert(bracketIndex, "border: 3px solid green;");
            }

            move_tiles[i]->setStyleSheet(stylesheet);
        }

        return;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}









