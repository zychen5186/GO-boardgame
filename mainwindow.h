#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QtGui>
#include <QtCore>
#include <QPainter>
#include "rematch.h"
#include "resign.h"
#include "gomoku.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *ev);
    void initialChess();
    void changeTurn();
    void fourDimensionCheck(int a, int b);
    bool stillAlive(int a,int b);
    void chessImpact(int a, int b, int c, int d);
    void clearDeadChess(int a, int b);
    void chessLifeInitialize();
    void updateLife();
    void set_if_checked_alive_if_killed();
    void initial_chess_avialable();



public:
    int whoseTurn=1;//1->blacks' turn, 2->whites' turn
    bool back_Flag = false;//to ensure back_event would not be implement over one time

private:
    Ui::MainWindow *ui;
    Rematch *rematch;
    Resign *resign;
    Gomoku *gomoku;
    //QGraphicsScene *scene;
    int chess_color[21][21];
    int chess_life[21][21];
    int chess_availble[21][21];//for special rule
    int previousStep[21][21];
    bool if_checked_alive[21][21];
    bool if_killed[21][21];

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void clearChess();
    void on_rematch_Button_clicked();
    void on_resignButton_clicked();
    void on_backButton_clicked();
    void change_if_white();
    void on_actionGomoku_triggered();
    void Create_board();
};





#endif // MAINWINDOW_H
