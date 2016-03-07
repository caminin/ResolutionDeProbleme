#ifndef __MYTABLE
#define __MYTABLE

#include "Piece.hpp"
#include "Chrono.hpp"
#include <list>


class Table
{
    
private:
    vector<  vector< Piece* > > mytable;
    int rows_count;
    int columns_count;
    
public:
    Table(int row_count, int columns_count);
    void addPiece(int row, int column,Piece* p);
    void removePiece(int row, int column);
    
    bool checkPiece(int row, int column,Piece *p);
    void rotate(int row, int column);
    
    void showTable();
    void getRes();
    
    Chrono algoCSP(vector<Piece*>& mypile);
};

#endif

