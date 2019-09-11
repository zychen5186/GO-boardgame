#ifndef RESIGN_H
#define RESIGN_H


#include <QWidget>

namespace Ui {
class Resign;
}

class Resign : public QWidget
{
    Q_OBJECT

public:
    explicit Resign(int a, QWidget *parent = nullptr);//constructor
    ~Resign();


signals:
    void clear();
private:
    Ui::Resign *ui;
public:
    int whoseturn=1;
private slots:
    void on_pushButton_clicked();
};

#endif // RESIGN_H
