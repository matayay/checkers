#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update_board();
    void end_game();

private slots:
    void on_game_btn_clicked();

private:
    Ui::MainWindow *ui;
    Board game_board_;

    QVector<QWidget*> silver_pieces_;
    QVector<QWidget*> gold_pieces_;
    QLabel *winner_label_ = nullptr;
};
#endif // MAINWINDOW_H
