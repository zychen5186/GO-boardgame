#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Go");
   // connect(ui->resignButton,SIGNAL(clicked()),this,SLOT(resignButton_clicked()));
   // connect(ui->rematch_Button,SIGNAL(clicked()),this,SLOT(on_rematch_Button_clicked()));

    /*this->scene = new QGraphicsScene(0,0,ui->graphicsView->width()-2,
                                    ui->graphicsView->height()-2);
    QSize boardSize(800,800);
    QPixmap board(":/new/prefix1/Blank_Go_board.png") ;
    QPixmap scaledBoard = board.scaled(boardSize,Qt::KeepAspectRatio);

    scene->addPixmap(scaledBoard);
    //scene->addEllipse(0,0,200,200);
    //ui->graphicsView->setScene(scene);
    //ui->graphicsView->mapFromScene();*/
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
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

void MainWindow::mousePressEvent(QMouseEvent *ev)
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
        if(chess_color[xPos][yPos]==0 && chess_availble[xPos][yPos]>0){
            for(int i=1;i<20;i++){//for back_button.
                for(int j=1;j<20;j++){
                    previousStep[i][j] = chess_color[i][j];
                }
            }
            if(whoseTurn == 1)
                chess_color[xPos][yPos] = 1;
            if(whoseTurn == 2)
                chess_color[xPos][yPos] = 2;
            updateLife();
           // printcolor();
            fourDimensionCheck(xPos,yPos);//check if there are any chess been eaten
            //from this line, already after chess impact
           qDebug() <<chess_color[xPos-1][yPos] << chess_color[xPos+1][yPos] <<
                   chess_color[xPos][yPos-1]<< chess_color[xPos][yPos+1];
            if(chess_color[xPos-1][yPos]!=0 && chess_color[xPos+1][yPos]!=0 &&
                    chess_color[xPos][yPos-1]!=0 && chess_color[xPos][yPos+1]!=0 &&
                    chess_color[xPos-1][yPos]!=whoseTurn && chess_color[xPos+1][yPos]!=whoseTurn &&
                    chess_color[xPos][yPos-1]!=whoseTurn && chess_color[xPos][yPos+1]!=whoseTurn){
                chess_color[xPos][yPos]=0;
            }
            else {
                changeTurn();
                back_Flag = true;
                update();
                for(int i=1;i<20;i++){
                    for(int j=1;j<20;j++){
                        chess_availble[i][j]+=1;//for special rule
                    }
                }
            }
        }
    }
}

void MainWindow::initialChess()
{
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
            chess_color[i][j] = 0;//0->blank,1->white,2->black;
        }
    }
    for(int i=0;i<21;i++){//->3 illegal
        chess_color[i][0] = 3;
        chess_color[i][20] = 3;
        chess_color[0][i] = 3;
        chess_color[20][i] = 3;
    }
    update();
}

void MainWindow::changeTurn()
{
    if(whoseTurn == 1)
        whoseTurn = 2;
    else
        whoseTurn = 1;
}

void MainWindow::fourDimensionCheck(int a, int b)
{
    //four direction checking
    if(a>1&&chess_color[a][b] !=chess_color[a-1][b]){
       //                 qDebug()<<"left checked";
        chessImpact(a,b,a-1,b);
    }
    if(a<19&&chess_color[a][b] !=chess_color[a+1][b]){
        //               qDebug()<<"right checked";
        chessImpact(a,b,a+1,b);
    }
    if(b>1&&chess_color[a][b] !=chess_color[a][b-1]){
         //               qDebug()<<"up cheched";
        chessImpact(a,b,a,b-1);
    }
    if(b<19&&chess_color[a][b] !=chess_color[a][b+1]){
         //               qDebug()<<"down checked";
        chessImpact(a,b,a,b+1);
    }
    if(a>1&&chess_color[a][b] ==chess_color[a-1][b]){
       //                 qDebug()<<"left checked";
        chessImpact(a,b,a-1,b);
    }
    if(a<19&&chess_color[a][b] ==chess_color[a+1][b]){
        //               qDebug()<<"right checked";
        chessImpact(a,b,a+1,b);
    }
    if(b>1&&chess_color[a][b] ==chess_color[a][b-1]){
         //               qDebug()<<"up cheched";
        chessImpact(a,b,a,b-1);
    }
    if(b<19&&chess_color[a][b] ==chess_color[a][b+1]){
         //               qDebug()<<"down checked";
        chessImpact(a,b,a,b+1);
    }
}

//wether the chess adjacent with [a][b] are dead or alive
bool MainWindow::stillAlive(int a,int b)
{
    qDebug()<<"still alive?";
    if_checked_alive[a][b]=false;
    bool left=false, right=false, up=false, down=false;
    //false means diff color or same color but no life
    if(a>1 && chess_color[a][b]==chess_color[a-1][b] && if_checked_alive[a-1][b]){
        if(chess_life[a-1][b]==0){
            if(stillAlive(a-1,b)){
                left = true;
            }
            else
                left = false;
        }
        else
            return true;//still have life
    }
    if(a<19 && chess_color[a][b]==chess_color[a+1][b] && if_checked_alive[a+1][b]){
        if(chess_life[a+1][b]==0){
            if(stillAlive(a+1,b)){
                right = true;
            }
            else
                right = false;
        }
        else
            return true;//still have life
    }
    if(b>1 && chess_color[a][b]==chess_color[a][b-1] && if_checked_alive[a][b-1]){
        if(chess_life[a][b-1]==0){
            if(stillAlive(a,b-1)){
                up = true;
            }
            else
                up = false;
        }
        else
            return true;//still have life
    }
    if(b<19 && chess_color[a][b]==chess_color[a][b+1] && if_checked_alive[a][b+1]){
        if(chess_life[a][b+1]==0){
            if(stillAlive(a,b+1)){
                down = true;
            }
            else
                down = false;
        }
        else
            return true;//still have life
    }
    if(left==true||right==true||down==true||up==true)
        return true;
    else {
        return false;
    }
}

void MainWindow::chessImpact(int a, int b, int c, int d)
{
    if(chess_color[c][d]!=0 && chess_color[a][b]==chess_color[c][d]){//same color
        //qDebug()<<"same color impact";
        //qDebug()<<a<<" "<<b<<":"<<chess_life[a][b]<<";"<<c<<" "<<d<<":"<<chess_life[c][d];
        if(chess_life[a][b]==0){
            set_if_checked_alive_if_killed();
            if(!stillAlive(a,b)){
                chess_color[a][b] = 0;
                changeTurn();
           }
        }
    }
    else if(chess_color[c][d]!=0 && chess_color[a][b]!=chess_color[c][d]){//diff color
    //  qDebug()<<"diff color impact";
    //  qDebug()<<a<<" "<<b<<":"<<chess_life[a][b]<<";"<<c<<" "<<d<<":"<<chess_life[c][d];

        if(chess_life[c][d]==0){
            set_if_checked_alive_if_killed();//avoid repeating checking the same chess
            if(!stillAlive(c,d)){
                clearDeadChess(c,d);//only clear chess which color are same with the dead chess.
                updateLife();
                if(chess_life[a][b]==1 && chess_life[c][d]==0)
                    chess_availble[c][d]=(-1);//for special rule
            }
        }

    }
}

void MainWindow::clearDeadChess(int a, int b)
{
   // qDebug()<<"kill"<<a<<b;
    if_killed[a][b]=false;
    if(a>1 && chess_color[a][b]==chess_color[a-1][b]&&if_killed[a-1][b]){//left
        clearDeadChess(a-1,b);
    }
    if(a<19 && chess_color[a][b]==chess_color[a+1][b]&&if_killed[a+1][b]){//right
        clearDeadChess(a+1,b);
    }
    if(b>1 && chess_color[a][b]==chess_color[a][b-1]&&if_killed[a][b-1]){//up
        clearDeadChess(a,b-1);
    }
    if(b<19 && chess_color[a][b]==chess_color[a][b+1]&&if_killed[a][b+1]){//down
        clearDeadChess(a,b+1);
    }
    chess_color[a][b] = 0;
    return;
}

/*void MainWindow::set_chess_position()//2->corner,3->edge,4->other
{
    chess_position[0][0]=2;
    chess_position[0][18]=2;
    chess_position[18][0]=2;
    chess_position[18][18]=2;
    for(int i=1;i<18;i++){
        chess_position[0][i]=3;
        chess_position[18][i]=3;
        chess_position[i][0]=3;
        chess_position[i][18]=3;
    }
    for(int i=1;i<18;i++){
        for(int j=1;j<18;j++){
            chess_position[i][j]=4;
        }
    }
}*/

void MainWindow::chessLifeInitialize()
{
    chess_life[1][1]=2;
    chess_life[1][19]=2;
    chess_life[19][1]=2;
    chess_life[19][19]=2;
    for(int i=2;i<19;i++){
        chess_life[1][i]=3;
        chess_life[19][i]=3;
        chess_life[i][1]=3;
        chess_life[i][19]=3;
    }
    for(int i=2;i<19;i++){
        for(int j=2;j<19;j++){
            chess_life[i][j]=4;
        }
    }
}

void MainWindow::updateLife()
{
    chessLifeInitialize();
    if(chess_color[1][2]!=0)
        chess_life[1][1]-=1;
    if(chess_color[2][1]!=0)
        chess_life[1][1]-=1;
    if(chess_color[1][18]!=0)
        chess_life[1][19]-=1;
    if(chess_color[2][19]!=0)
        chess_life[1][19]-=1;
    if(chess_color[18][19]!=0)
        chess_life[19][19]-=1;
    if(chess_color[19][18]!=0)
        chess_life[19][19]-=1;
    if(chess_color[18][1]!=0)
        chess_life[19][1]-=1;
    if(chess_color[19][2]!=0)
        chess_life[19][1]-=1;
    for(int i=2;i<19;i++){
        if(chess_color[1][i-1]!=0)
            chess_life[1][i]-=1;
        if(chess_color[1][i+1]!=0)
            chess_life[1][i]-=1;
        if(chess_color[2][i]!=0)
            chess_life[1][i]-=1;
        if(chess_color[19][i-1]!=0)
            chess_life[19][i]-=1;
        if(chess_color[19][i+1]!=0)
            chess_life[19][i]-=1;
        if(chess_color[18][i]!=0)
            chess_life[19][i]-=1;
        if(chess_color[i-1][1]!=0)
            chess_life[i][1]-=1;
        if(chess_color[i+1][1]!=0)
            chess_life[i][1]-=1;
        if(chess_color[i][2]!=0)
            chess_life[i][1]-=1;
        if(chess_color[i-1][19]!=0)
            chess_life[i][19]-=1;
        if(chess_color[i+1][19]!=0)
            chess_life[i][19]-=1;
        if(chess_color[i][18]!=0)
            chess_life[i][19]-=1;
    }
    for(int i=2;i<19;i++){
        for(int j=2;j<19;j++){
            if(chess_color[i-1][j]!=0)
                chess_life[i][j]-=1;
            if(chess_color[i][j-1]!=0)
                chess_life[i][j]-=1;
            if(chess_color[i+1][j]!=0)
                chess_life[i][j]-=1;
            if(chess_color[i][j+1]!=0)
                chess_life[i][j]-=1;
        }
    }
}

void MainWindow::set_if_checked_alive_if_killed()//avoid repeatting checking causes error
{
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
            if_checked_alive[i][j]=true;
            if_killed[i][j]=true;
        }
    }
}

void MainWindow::initial_chess_avialable()
{
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
           chess_availble[i][j]=1;
        }
    }
}

void MainWindow::change_if_white()
{
    if(whoseTurn==2)
        changeTurn();
}

void MainWindow::clearChess()
{
    for(int i=1;i<20;i++){
        for(int j=1;j<20;j++){
            chess_color[i][j] = 0;//0->blank,1->white,2->black;
        }
    }
    for(int i=0;i<21;i++){//->3 illegal
        chess_color[i][0] = 3;
        chess_color[i][20] = 3;
        chess_color[0][i] = 3;
        chess_color[20][i] = 3;
    }
    update();
}

void MainWindow::on_rematch_Button_clicked()
{
    rematch = new Rematch();
    rematch->show();
    connect(rematch,SIGNAL(clear()),this,SLOT(change_if_white()));
    connect(rematch,SIGNAL(clear()),this,SLOT(clearChess()));


}

void MainWindow::on_resignButton_clicked()
{
    resign = new Resign(whoseTurn);
    resign->show();
    connect(resign,SIGNAL(clear()),this,SLOT(clearChess()));
    change_if_white();
}

void MainWindow::on_backButton_clicked()
{
    if(back_Flag == true){
        for(int i=1;i<20;i++){
            for(int j=1;j<20;j++){
                chess_color[i][j] = previousStep[i][j];
            }
        }
        back_Flag = false;//avoid reapeting calling back function
        changeTurn();
        update();
        for(int i=1;i<20;i++){
            for(int j=1;j<20;j++){
                chess_availble[i][j]-=1;
            }
        }
    }
}

void MainWindow::on_actionGomoku_triggered()
{
    gomoku = new Gomoku();
    gomoku->show();
    connect(gomoku,SIGNAL(changeGame()),this,SLOT(Create_board()));
    close();
}

void MainWindow::Create_board()
{
    initialChess();
    show();
}
