#include "../include/Piece.hpp"


Piece::Piece(vector<int> _color, Rotation _rotation)
{
    mycolor=_color;
    myrotation=_rotation;
}


void Piece::rotation1()
{
    
}

void Piece::rotation2()
{
    
}

int Piece::getColor1(int face)
{
    return 0;
}

int Piece::getColor2(int face)
{
    return 0;
}

string
Piece::to_string()
{
    string res="Pièce de couleur "+std::to_string(mycolor[0])+"/"+std::to_string(mycolor[1])+"/"+std::to_string(mycolor[2])+"/"+std::to_string(mycolor[3]);
    
    return res;
}
