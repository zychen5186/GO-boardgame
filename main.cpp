#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.initialChess();
    w.initial_chess_avialable();
    //w.set_chess_position();
    //w.chessLifeInitialize();

    return a.exec();
}
