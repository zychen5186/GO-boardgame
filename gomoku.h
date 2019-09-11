#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include "livethreewarning.h"
#include "gomokuend.h"


namespace Ui {
class Gomoku;
}

class Gomoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gomoku(QWidget *parent = nullptr);
    ~Gomoku();
    void mousePressEvent(QMouseEvent *ev);
    void initialChess();
    void changeTurn();
    void eightDimensionCheck(int a,int b);
    void check_if_live_three(int a,int b,int c,int d);
    void check_if_end(int a,int b,int c,int d);



public:
    int whoseTurn = 1;//1->blacks' turn, 2->whites' turn
    bool back_Flag = false;//to ensure back_event would not be implement over one time
    int liveThreeCount = 0;
    int endCount = 0;

private:
    Ui::Gomoku *ui;
    Gomoku *gomoku;
    gomokuend *Mgomokuend;
    liveThreeWarning *live3warning;
    //QGraphicsScene *scene;
    int chess_color[21][21];
    int previousStep[21][21];

signals:
    void live_three_warning();
    void gameEnd();
    void changeGame();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_back_Button_clicked();
    void live3warning_slot();
    void gameEnd_slot();
    void clearchess();
    void on_actionGo_triggered();
};

#endif // GOMOKU_H
