#ifndef REMATCH_H
#define REMATCH_H

#include <QDialog>

namespace Ui {
class Rematch;
}

class Rematch : public QDialog
{
    Q_OBJECT

public:
    explicit Rematch(QWidget *parent = nullptr);
    ~Rematch();
public:
    Ui::Rematch *ui;

signals:
    void clear();

private slots:
    void on_yesButton_clicked();
    void on_noButton_clicked();
};

#endif // REMATCH_H
