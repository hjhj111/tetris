#include "tetris.h"


#include<QPainter>
#include<QDebug>
#include<QMessageBox>
#include<QKeyEvent>


Tetris::Tetris(QWidget *parent) : QWidget(parent)
{
    row=50;
    col=30;
    d=10;
    time=300;
    score=0;

    board=QVector<QVector<int>>(row,QVector<int>(col,0));
    _board=QVector<QVector<int>>(row,QVector<int>(col,0));

    this->setFixedSize(d*(col+2),d*(row+2));
    this->setWindowFlag(Qt::FramelessWindowHint);

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(autoMove()));

}

void Tetris::drawWall()
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::green));
    //画上下两行墙
    for(int i=0;i<col+2;i++)
    {
        painter->drawRect(i*d,0,d,d);
        painter->drawRect(i*d,d*(row+1),d,d);
    }
    //画左右两列墙
    for(int i=0;i<row+2;i++)
    {
        painter->drawRect(0,i*d,d,d);
        painter->drawRect(d*(col+1),i*d,d,d);
    }
    painter->end();
}

void Tetris::drawBoard()
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::blue));
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==1)
            {
                //qDebug()<<"a kuai";
                painter->drawRect(j*d+d,i*d+d,d,d);
            }
        }
    }
    painter->end();
}

void Tetris::draw_Board()
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::yellow));
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(_board[i][j]==1)
            {

                painter->drawRect(j*d+d,i*d+d,d,d);
            }
        }
    }
    painter->end();
}


void Tetris::paintEvent(QPaintEvent *)
{
    painter=new QPainter;
    drawWall();
    draw_Board();
    drawBoard();
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"key";
    switch (event->key())
    {
    case Qt::Key_Left:
        if(canMoveLeft())
        {
            update();
        }
        else
        {
            //qDebug()<<"cant left";
        }
        break;
    case Qt::Key_Right:
        if(canMoveRight())
        {
            update();
        }
        else
        {
            //qDebug()<<"cant right";
        }
        break;
    case Qt::Key_Down:
        if(canMoveDown())
        {
            update();
        }
        else
        {
            //qDebug()<<"cant right";
        }
        break;
    case Qt::Key_Up:
        if(canTurn())
        {
            update();
        }
        else
        {
            qDebug()<<"cant turn";
        }
        break;
    default:
        break;

    }
}

void Tetris::update_Board()
{
    _board=QVector<QVector<int>>(row,QVector<int>(col,0));
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(item.itemBoard[i][j]==1)
            {
                int tmpRow=item.itemRow+i-1;
                int tmpCol=item.itemCol+j-1;
                if(tmpRow>=0&&tmpRow<row&&tmpCol<col&&tmpCol>=0)
                {
                    _board[tmpRow][tmpCol]=1;
                }

            }
        }
    }
    tmp_board=_board;
}

void Tetris::undo_Board()
{
    _board=tmp_board;
}

void Tetris::autoMove()
{

    if(gameOver())
    {
        timer->stop();
        QMessageBox::information(this,"game over","game over");
    }
    if(canMoveDown())
    {
        update();
    }
    else
    {
        updateBoard();
        update();
        clear();
        item=items.head();
        addRandItem();
        items.dequeue();
        update_Board();
        update();
    }
}

bool Tetris::canMoveDown()
{
    item.itemRow+=1;
    update_Board();
    if(item.itemRow==row-1&&(item.itemBoard[2][0]==1||item.itemBoard[2][1]==1||item.itemBoard[2][2]==1)||item.itemRow>row-1)
    {
        item.itemRow-=1;
        undo_Board();
        return false;
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==1&&_board[i][j]==1)
            {
                item.itemRow-=1;
                update_Board();
                return false;
            }
        }
    }
    return true;
}

bool Tetris::canMoveLeft()
{
    item.itemCol-=1;
    update_Board();
    if(item.itemCol<0||item.itemCol==0&&(item.itemBoard[0][0]==1||item.itemBoard[1][0]==1||item.itemBoard[2][0]==1))
    {
        item.itemCol+=1;
        update_Board();
        return false;
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==1&&_board[i][j]==1)
            {
                item.itemCol+=1;
                update_Board();
                return false;
            }
        }
    }
    return true;
}

bool Tetris::canMoveRight()
{
    item.itemCol+=1;
    update_Board();
    if(item.itemCol>col-1||item.itemCol==col-1&&(item.itemBoard[0][1]==1||item.itemBoard[1][1]==1||item.itemBoard[2][1]==1))
    {
        item.itemCol-=1;
        update_Board();
        return false;
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==1&&_board[i][j]==1)
            {
                item.itemCol-=1;
                update_Board();
                return false;
            }
        }
    }
    return true;
}

bool Tetris::canTurn()
{
    item.turn();
    update_Board();
    if(item.itemRow==row-1&&(item.itemBoard[2][0]==1||item.itemBoard[2][1]==1||item.itemBoard[2][2]==1)||
            item.itemCol==0&&(item.itemBoard[0][0]==1||item.itemBoard[1][0]==1||item.itemBoard[2][0]==1)||
            item.itemCol==col-1&&(item.itemBoard[0][1]==1||item.itemBoard[1][1]==1||item.itemBoard[2][1]==1))
    {
        item.itemCol-=1;
        update_Board();
        return false;
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(board[i][j]==1&&_board[i][j]==1)
            {
                item.unturn();
                update_Board();
                return false;
            }
        }
    }
    return true;
}

bool Tetris::gameOver()
{
    for(int i=0;i<col;i++)
    {
        if(board[0][i]==1)
        {
            return true;
        }
    }
    return false;
}

void Tetris::updateBoard()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(item.itemBoard[i][j]==1)
            {
                int tmpRow=item.itemRow+i-1;
                int tmpCol=item.itemCol+j-1;
                board[tmpRow][tmpCol]=1;
            }
        }
    }

}

void Tetris::clear()
{
    int _row=row-1;
    while(_row>0)
    {
        while(canClear(_row))
        {
            clearOne(_row);
            score+=10;
        }
        _row--;
    }
}

void Tetris::clearOne(int _row)
{
    if(canClear(_row))
    {
        for(int i=_row;i>0;i--)
        {
            board[i]=board[i-1];
        }
        board[0]=QVector<int>(col,0);
    }
    update();
}

bool Tetris::canClear(int _row)
{
    for(int i=0;i<col;i++)
    {
        if(board[_row][i]==0)
        {
            return false;
        }
    }
    return true;
}

void Tetris::addRandItem()
{
    int randint=rand()%2;
    switch (randint)
    {
    case 0:
        items.enqueue(Item(row,col));
        break;
    case 1:
        items.enqueue(Iteml(row,col));
        break;
    default:
        break;
    }
}

void Tetris::newGame()
{
    if(score>maxScore)
    {
        maxScore=score;
    }
    board=QVector<QVector<int>>(row,QVector<int>(col,0));
    _board=QVector<QVector<int>>(row,QVector<int>(col,0));

    addRandItem();
    addRandItem();
    addRandItem();
    item=Item(row,col);
    items.dequeue();
    update_Board();
    score=0;

    timer->start(time);
}
