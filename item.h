#ifndef ITEM_H
#define ITEM_H
#include <QVector>


class Item
{
public:
    Item(int row,int col);
    Item();
    QVector<QVector<int>>itemBoard;
    virtual void innitialize();
    void turn();
    void unturn();
    int itemRow;
    int itemCol;
    int row;
    int col;
};

#endif // ITEM_H
