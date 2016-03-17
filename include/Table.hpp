#ifndef __MYTABLE
#define __MYTABLE

#include "Piece.hpp"
#include "Chrono.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

enum PIECE_STATUS {INTERIEUR,BORD,COIN};

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
    
    pair<int,int> getCorner(int id);
    pair<int,int> getBorder(int id);
    pair<int,int> getInsider(int id);
    
    void insertCorner(int row, int column,Piece* p);
    void insertBorder(int row, int column,Piece* p);
    void insertInsider(int row, int column,Piece* p);
    
    int getBestRotation(int row, int column,Piece* p,PIECE_STATUS piece);
    
    int numberOfErrors(int row, int column,Piece* p,int rotation=-1);
    bool betterSwap(int row1, int column1, int row2, int column2,PIECE_STATUS piece);
    
};

#endif

