#ifndef __MYPiece
#define __MYPiece

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

enum Face{BAS,GAUCHE,HAUT,DROITE};

class Piece
{
private:
    static int id_all;
    int id;
    int myrotation;
    bool placed;
    int* mycolor;
    
    int **index_tab;

    
public:
    Piece(vector<int> _color, int _rotation); 
    
    void setRotation(int new_rotation);
    int getRotation(){return myrotation;}
    
    void setPlaced(){placed=true;}
    void setUnplaced(){placed=false;}
    bool getPlaced(){return placed;}
    int getId(){return id;}
    
    void rotation();
    
    int getColor(int face);
    int borderCount();
    
    string to_string();
    bool operator==(Piece p1);
    
    
};






#endif
