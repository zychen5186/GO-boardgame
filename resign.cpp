#include "resign.h"
#include "ui_resign.h"

Resign::Resign(int a, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resign)
{
    ui->setupUi(this);
    whoseturn = a;
    if(whoseturn == 2){
        ui->label->setText("White wins the game!!!");
    }
    if(whoseturn == 1){
        ui->label->setText("Black wins the game!!!");
    }
    setWindowTitle("RESIGN");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
}

/*Resign::Resign(int a)
{
    whosturn = a;
}*/

void Resign::on_pushButton_clicked()
{
    emit clear();
    close();
}

Resign::~Resign()
{
    delete ui;
}


