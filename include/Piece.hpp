#ifndef __MYPiece
#define __MYPiece

#include <vector>
#include <string>

using namespace std;

enum Rotation{BAS,GAUCHE,HAUT,DROITE};

class Piece
{
private:
    Rotation myrotation;
    vector<int> mycolor;

    
public:
    Piece(vector<int> _color, Rotation _rotation); 
    void rotation1();
    void rotation2();
    
    int getColor1(int face);
    int getColor2(int face);
    
    string to_string();
    
    
};






#endif
