#ifndef ITEML_H
#define ITEML_H

#include "item.h"

class Iteml : public Item
{
public:
    Iteml(int row,int w);
    Iteml();
    void innitialize()override;
};

#endif // ITEML_H
