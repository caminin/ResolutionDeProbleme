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
    uniform_int_distribution<int> uni_row;
    uniform_int_distribution<int> uni_column;
    mt19937 rng;
    
    int number_of_corners;
    int number_of_borders;
    int number_of_insiders;
    
    std::uniform_int_distribution<int> uni_corners;
    std::uniform_int_distribution<int> uni_borders;
    std::uniform_int_distribution<int> uni_insiders;

    
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
    Chrono test(vector<Piece*> &mypile);
    Chrono algoLocalSearch(vector<Piece*> &mypile);
    
    pair<int,int> getCorner(int id);
    pair<int,int> getBorder(int id);
    pair<int,int> getInsider(int id);
    bool isNeighbour(int row1, int column1,int row2, int column2);
    pair<int,int> getPieceForSearch(int initial_row,int initial_column, PIECE_STATUS piece,std::mt19937 &rng, int &saved_error);
    int getNumberOfAllError();
    
    PIECE_STATUS getStatus(int row, int column);
    
    void insertCorner(int row, int column,Piece* p);
    void insertBorder(int row, int column,Piece* p);
    void insertInsider(int row, int column,Piece* p);
    void swap(int row1, int column1, int row2, int column2,PIECE_STATUS piece);
    void degeneration(int initial_row, int initial_column, PIECE_STATUS piece,std::mt19937 &rng);
    
    int getBestRotation(int row, int column,Piece* p,PIECE_STATUS piece);
    pair<int,int> getBestRotationNeighbour(int row1, int column1,int row2, int column2,int &error,PIECE_STATUS piece);
    
    int numberOfErrors(int row, int column,Piece* p,int rotation=-1);
    int betterSwap(int row1, int column1, int row2, int column2,PIECE_STATUS piece);
    
};

#endif

