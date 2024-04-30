#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    placeCheckers();
}

void MainWindow::placeCheckers() {
    // Define the styles for the checker pieces
    QString silver_piece_style = "background-color: white; border-radius: 40px;";
    QString gold_piece_style = "background-color: gold; border-radius: 40px;";

    int pieceSize = 80;
    int offset = (100 - pieceSize) / 2;

    // Loop to place silver checker pieces on the first three rows
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 0) { // Place on gold
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);
                if (tile) {
                    QWidget *silver_piece = new QWidget(tile);
                    silver_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    silver_piece->setStyleSheet(silver_piece_style);
                    silver_piece->show();
                    silver_pieces_.append(silver_piece);
                }
            }
        }
    }

    // Loop to place gold checker pieces on the last three rows
    for (int row = 5; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 0) { // Place on gold tiles
                QString tileObjectName = QString("tile%1%2").arg(row, 1, 10, QChar('0')).arg(col, 1, 10, QChar('0'));
                QWidget *tile = findChild<QWidget *>(tileObjectName);
                if (tile) {
                    QWidget *gold_piece = new QWidget(tile);
                    gold_piece->setGeometry(offset, offset, pieceSize, pieceSize);
                    gold_piece->setStyleSheet(gold_piece_style);
                    gold_piece->show();
                    gold_pieces_.append(gold_piece);
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
