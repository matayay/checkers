#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
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
    void delete_pieces();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void on_game_btn_clicked();
    void handleClickedPiece(const QString& objectName);

private:
    Ui::MainWindow *ui;
    Board game_board_;

    QVector<QWidget*> tiles_;
    QVector<QWidget*> silver_pieces_;
    QVector<QWidget*> gold_pieces_;
    QLabel *winner_label_ = nullptr;

    std::pair<int, int> *selected_piece_ = nullptr;
};
#endif // MAINWINDOW_H
