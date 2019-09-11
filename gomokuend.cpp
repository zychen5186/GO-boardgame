#include "gomokuend.h"
#include "ui_gomokuend.h"

gomokuend::gomokuend(int a,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gomokuend)
{
    ui->setupUi(this);
    if(a == 1)
        ui->label->setText("!!!!Black Wins!!!!");
    if(a == 2)
        ui->label->setText("!!!!White Wins!!!!");

}

gomokuend::~gomokuend()
{
    delete ui;
}

void gomokuend::on_pushButton_clicked()
{
    emit clear();
    close();
}
