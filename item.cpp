#include "item.h"

Item::Item(int row ,int col)
    :row(row),col(col)
{
    innitialize();
}
Item::Item()
{

}

void Item::innitialize()
{
    itemCol=col/2;
    itemRow=1;
    itemBoard.fill(QVector<int>{1,1,1},3);
}

void Item::turn()
{
    QVector<QVector<int>>tmp(itemBoard);
    for(int i=0;i<3;i++)
    {
        itemBoard[0][i]=tmp[i][2];
        itemBoard[2][i]=tmp[i][0];
    }
    itemBoard[1][0]=tmp[0][1];
    itemBoard[1][2]=tmp[2][1];
}

void Item::unturn()
{
    QVector<QVector<int>>tmp(itemBoard);
    for(int i=0;i<3;i++)
    {
        itemBoard[i][2]=tmp[0][i];
        itemBoard[i][0]=tmp[2][i];
    }
    itemBoard[0][1]=tmp[1][0];
    itemBoard[2][1]=tmp[1][2];
}
