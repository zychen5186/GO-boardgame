#include "rematch.h"
#include "ui_rematch.h"

Rematch::Rematch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rematch)
{
    ui->setupUi(this);
    setWindowTitle("REMATCH");
    connect(ui->yesButton, SIGNAL(clicked()),this,SLOT(on_yesButton_clicked()));
    connect(ui->noButton,SIGNAL(clicked()),this,SLOT(on_noButton_clicked()));
}

Rematch::~Rematch()
{
    delete ui;
}

void Rematch::on_yesButton_clicked()
{
    emit clear();
    close();
}

void Rematch::on_noButton_clicked()
{
    close();
}
