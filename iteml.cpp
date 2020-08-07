
#include "iteml.h"

Iteml::Iteml(int row,int col)
    :Item(row,col)
{
    innitialize();
}

void Iteml::innitialize()
{
    Item::innitialize();
    itemBoard[0][1]=0;
    itemBoard[0][2]=0;
    itemBoard[1][1]=0;
    itemBoard[1][2]=0;
    itemBoard[2][2]=0;
}
