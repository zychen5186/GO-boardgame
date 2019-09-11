#include "gomoku.h"
#include "ui_gomoku.h"

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku)
{
    ui->setupUi(this);
    setWindowTitle("Gomoku");
    initialChess();
    connect(this,SIGNAL(live_three_warning()),this,SLOT(live3warning_slot()));
    connect(this,SIGNAL(gameEnd()),this,SLOT(gameEnd_slot()));

}

Gomoku::~Gomoku()
{
    delete ui;
}

void Gomoku::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen(Qt::black,2,Qt::SolidLine,Qt::FlatCap,Qt::RoundJoin);
    QPen pointpen(Qt::black);
    pointpen.setWidth(8);
    QPen chessPen(Qt::black);
    chessPen.setWidth(1);
    QBrush blackBrush(Qt::black,Qt::SolidPattern);
    QBrush whiteBrush(Qt::white,Qt::SolidPattern);
    painter.setPen(pen);
    for(int i=0;i<19;i++){
        painter.drawLine(20,40+i*40,740,40+i*40);
        painter.drawLine(20+i*40,40,20+i*40,760);
    }
    painter.setPen(pointpen);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            painter.drawPoint(140+i*240,160+j*240);
        }
    }
    painter.setPen(chessPen);
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
            switch (chess_color[i][j]) {
                case 0:
                    break;
                case 1:
                    painter.setBrush(blackBrush);
                    painter.drawEllipse(0+(i-1)*40,20+(j-1)*40,37,37);//1 ->black
                    break;
                case 2:
                    painter.setBrush(whiteBrush);
                    painter.drawEllipse(0+(i-1)*40,20+(j-1)*40,37,37);//2 ->white
                    break;
                default:
                    break;
            }
        }
    }

}

void Gomoku::mousePressEvent(QMouseEvent *ev)
{
    int xPos = 1,yPos=1;
//avoid pointing outside the board
    if(ev->x()>0&&ev->x()<760&&ev->y()>20&&ev->y()<780){
//use for loop to inspect which interval the cursor is in.
        for(int i=0;i<19;i++){
            if(i*40 <= ev->x() && 40+i*40 > ev->x()){
                xPos = i+1;
                break;
            }
        }
        for(int j=0;j<19;j++){
            if(j*40+20 <= ev->y() && j*40+60 > ev->y()){
                yPos = j+1;
                break;
            }
        }
        //makes movement in here
        //avoid pointing on a place which is not empty
        if(chess_color[xPos][yPos]==0){
            for(int i=1;i<20;i++){//for back_button.
                for(int j=1;j<20;j++){
                    previousStep[i][j] = chess_color[i][j];
                }
            }
            if(whoseTurn == 1)
                chess_color[xPos][yPos] = 1;
            if(whoseTurn == 2)
                chess_color[xPos][yPos] = 2;
            eightDimensionCheck(xPos,yPos);
            changeTurn();
            update();
            back_Flag = true;
        }
    }
}

void Gomoku::initialChess()
{
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
            chess_color[i][j] = 0;//0->blank,1->white,2->black;
        }
    }
    for(int i=0;i<21;i++){
        chess_color[i][0] = 3;//3->illegal
        chess_color[i][20] = 3;
        chess_color[0][i] = 3;
        chess_color[20][i] = 3;
    }
    update();
}

void Gomoku::changeTurn()
{
    if(whoseTurn == 1)
        whoseTurn = 2;
    else
        whoseTurn = 1;
}

void Gomoku::eightDimensionCheck(int a, int b)
{
    endCount = 0;
    liveThreeCount = 0;
    check_if_live_three(a,b,a-1,b);//left
    check_if_end(a,b,a-1,b);
    if(endCount == 0 && liveThreeCount==0){//top left
        check_if_live_three(a,b,a-1,b-1);
        check_if_end(a,b,a-1,b-1);
    }
    if(endCount == 0 && liveThreeCount==0){//top
        check_if_live_three(a,b,a,b-1);
        check_if_end(a,b,a,b-1);
    }
    if(endCount == 0 && liveThreeCount==0){//top right
        check_if_live_three(a,b,a+1,b-1);
        check_if_end(a,b,a+1,b-1);
    }
    if(endCount == 0 && liveThreeCount==0){//right
        check_if_live_three(a,b,a+1,b);
        check_if_end(a,b,a+1,b);
    }
    if(endCount == 0 && liveThreeCount==0){//bottom right
        check_if_live_three(a,b,a+1,b+1);
        check_if_end(a,b,a+1,b+1);
    }
    if(endCount == 0 && liveThreeCount==0){//bottom
        check_if_live_three(a,b,a,b+1);
        check_if_end(a,b,a,b+1);
    }
    if(endCount == 0 && liveThreeCount==0){//bottom left
        check_if_live_three(a,b,a-1,b+1);
        check_if_end(a,b,a-1,b+1);
    }
    if(endCount>0){
        gameEnd();
    }
    if(liveThreeCount > 0){
        live_three_warning();
    }
}

void Gomoku::check_if_live_three(int a,int b,int c,int d)
{
    int X = c-a;
    int Y = d-b;
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==0 &&
            chess_color[a-X*1][b-Y*1]==whoseTurn && chess_color[a-X*2][b-Y*2]==0){
       liveThreeCount++;
    }
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==whoseTurn &&
           chess_color[a+X*3][b+Y*3]==0 && chess_color[a-X*1][b-Y*1]==0){//xOoox
            liveThreeCount++;
    }
    if(chess_color[a-X*1][b-Y*1]==whoseTurn && chess_color[a-X*2][b-Y*2]==0 &&
        chess_color[a+X*1][b+Y*1]==0 && chess_color[a+X*2][b+Y*2]==whoseTurn&&
        chess_color[a+X*3][b+Y*3]==0 ){//xoOxox
        liveThreeCount++;
    }
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==0 &&
        chess_color[a+X*3][b+Y*3]==whoseTurn && chess_color[a+X*4][b+Y*4]==0 &&
        chess_color[a-X*1][b-Y*1]==0 ){//xOoxox
        liveThreeCount++;
    }
    if(chess_color[a+X*1][b+Y*1]==0 && chess_color[a+X*2][b+Y*2]==whoseTurn &&
        chess_color[a+X*3][b+Y*3]==whoseTurn && chess_color[a+X*4][b+Y*4]==0&&
        chess_color[a-X*1][b-Y*1]==0 ){//xOxoox
        liveThreeCount++;
    }
}

void Gomoku::check_if_end(int a, int b, int c, int d)
{
    int X = c-a;
    int Y = d-b;
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==whoseTurn &&
            chess_color[a-X*1][b-Y*1]==whoseTurn && chess_color[a-X*2][b-Y*2]==whoseTurn){
       endCount++;
    }
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==whoseTurn &&
            chess_color[a+X*3][b+Y*3]==whoseTurn && chess_color[a-X*1][b-Y*1]==whoseTurn){
       endCount++;
    }
    if(chess_color[a+X*1][b+Y*1]==whoseTurn && chess_color[a+X*2][b+Y*2]==whoseTurn &&
            chess_color[a+X*3][b+Y*3]==whoseTurn && chess_color[a+X*4][b+Y*4]==whoseTurn){
       endCount++;
    }
}

void Gomoku::on_back_Button_clicked()
{
    if(back_Flag == true){
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                chess_color[i][j] = previousStep[i][j];
            }
        }
        back_Flag = false;//avoid reapeting calling back function
        changeTurn();
        update();
    }
}

void Gomoku::live3warning_slot()
{
    live3warning = new liveThreeWarning(whoseTurn);
    live3warning->show();
}

void Gomoku::gameEnd_slot()
{
    Mgomokuend = new gomokuend(whoseTurn);
    Mgomokuend->show();
    connect(Mgomokuend,SIGNAL(clear()),this,SLOT(clearchess()));
}

void Gomoku::clearchess()
{
    initialChess();
}

void Gomoku::on_actionGo_triggered()
{
    emit changeGame();
    close();
}
