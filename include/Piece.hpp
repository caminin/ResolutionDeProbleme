#ifndef __MYPiece
#define __MYPiece

#include <vector>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

enum Face{BAS,GAUCHE,HAUT,DROITE};

class Piece
{
private:
    static int id_all;
    int id;
    int myrotation;
    bool placed;
    vector<int> mycolor;

    
public:
    Piece(vector<int> _color, int _rotation); 
    
    void setRotation(int new_rotation);
    int getRotation(){return myrotation;}
    void setPlaced(){placed=true;}
    void setUnplaced(){placed=false;}
    bool getPlaced(){return placed;}
    int getId(){return id;}
    
    bool isInside(vector<  vector<pair<Piece*,int > > > &mytable);
    
    void rotation();
    void rotation1();
    void rotation2();
    
    int getColor(Face face);
    int getColor1(Face face);
    int getColor2(Face face);
    
    string to_string();
    bool operator==(Piece p1);
    
    
};






#endif
