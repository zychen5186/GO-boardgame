#ifndef GOMOKUEND_H
#define GOMOKUEND_H

#include <QWidget>

namespace Ui {
class gomokuend;
}

class gomokuend : public QWidget
{
    Q_OBJECT

public:
    explicit gomokuend(int a,QWidget *parent = nullptr);
    ~gomokuend();

private slots:
    void on_pushButton_clicked();

signals:
    void clear();

private:
    Ui::gomokuend *ui;
};

#endif // GOMOKUEND_H
