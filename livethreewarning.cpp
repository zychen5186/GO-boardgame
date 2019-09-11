#include "livethreewarning.h"
#include "ui_livethreewarning.h"

liveThreeWarning::liveThreeWarning(int a,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::liveThreeWarning)
{
    ui->setupUi(this);
    if(a == 1)
        ui->label->setText("!!!!Black has a live 3!!!!");
    if(a == 2)
        ui->label->setText("!!!!White has a live 3!!!!");
}

liveThreeWarning::~liveThreeWarning()
{
    delete ui;
}

void liveThreeWarning::on_pushButton_clicked()
{
    close();
}
