#include "../include/Table.hpp"


Table::Table(int rows_count,int columns_count)
{
    
    mytable.resize(rows_count,vector<Piece*>(columns_count));
}
