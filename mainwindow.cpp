#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game_board_ = Board();
}


void MainWindow::update_board()
{
    // Define the styles for the checker pieces
    QString silver_piece_style = "background-color: white; border-radius: 40px;";
    QString silver_king_style = "background-color: white; border-radius: 40px; border: 5px solid red;";

    QString gold_piece_style = "background-color: gold; border-radius: 40px;";
    QString gold_king_style = "background-color: gold; border-radius: 40px; border: 5px solid red;";

    int pieceSize = 80;
    int offset = (100 - pieceSize) / 2;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (game_board_.get_piece(row, col) == PieceType::Gold)
            {
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);

                if (tile)
                {
                    QWidget *gold_piece = new QWidget(tile);
                    gold_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    gold_piece->setStyleSheet(gold_piece_style);

                    QString piece_object_name = QString("p%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                    gold_piece->setObjectName(piece_object_name);

                    gold_piece->show();
                    gold_pieces_.append(gold_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::GoldKing)
            {
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);

                if (tile)
                {
                    QWidget *gold_piece = new QWidget(tile);
                    gold_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    gold_piece->setStyleSheet(gold_king_style);

                    gold_piece->show();
                    gold_pieces_.append(gold_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::Silver)
            {
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);

                if (tile)
                {
                    QWidget *silver_piece = new QWidget(tile);
                    silver_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    silver_piece->setStyleSheet(silver_piece_style);

                    silver_piece->show();
                    silver_pieces_.append(silver_piece);
                }
            }

            else if (game_board_.get_piece(row, col) == PieceType::SilverKing)
            {
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);

                if (tile)
                {
                    QWidget *silver_piece = new QWidget(tile);
                    silver_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    silver_piece->setStyleSheet(silver_king_style);

                    silver_piece->show();
                    silver_pieces_.append(silver_piece);
                }
            }
        }
    }
}


void MainWindow::end_game()
{
    ui->game_btn->setText("Start Game");

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
    }

    else if (ui->game_btn->text() == "End Game")
    {
        end_game();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
