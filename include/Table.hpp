#ifndef __MYTABLE
#define __MYTABLE

#include "Piece.hpp"


class Table
{
    
private:
    vector< vector<Piece*> > mytable;
    
public:
    Table(int row_count, int columns_count);
    
};

#endif
