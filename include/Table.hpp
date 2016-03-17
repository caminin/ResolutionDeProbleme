#ifndef __MYTABLE
#define __MYTABLE

#include "Piece.hpp"
#include "Chrono.hpp"
#include <list>
#include <iostream>
#include <fstream>

class Table
{
    
private:
    Piece* **mytable;
    vector<vector<int> > mytable_rotation;
    int rows_count;
    int columns_count;
    
public:
    Table(int row_count, int columns_count);
    void addPiece(int row, int column,Piece* p,int rot);
    void removePiece(int row, int column);
    
    bool checkPiece(int row, int column,Piece *p);
    void rotate(int row, int column);
    
    void showTable();
    void getRes(string row, string column);
    
    Chrono algoCSP(vector<Piece*>& mypile);
    
    void instanciation(vector<Piece*> &mypile);
    Chrono algoLocalSearch(vector<Piece*> &mypile);
    
};

#endif

