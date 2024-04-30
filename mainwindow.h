#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void placeCheckers();

private:
    Ui::MainWindow *ui;
    QVector<QWidget*> silver_pieces_;
    QVector<QWidget*> gold_pieces_;
};
#endif // MAINWINDOW_H
