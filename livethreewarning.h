#ifndef LIVETHREEWARNING_H
#define LIVETHREEWARNING_H

#include <QWidget>

namespace Ui {
class liveThreeWarning;
}

class liveThreeWarning : public QWidget
{
    Q_OBJECT

public:
    explicit liveThreeWarning(int a,QWidget *parent = nullptr);
    ~liveThreeWarning();

private slots:
    void on_pushButton_clicked();

private:
    Ui::liveThreeWarning *ui;
};

#endif // LIVETHREEWARNING_H
