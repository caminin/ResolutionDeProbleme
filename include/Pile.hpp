#ifndef __MYPILE
#define __MYPILE

#include "Piece.hpp"

class Pile
{
private:
    vector <Piece*> mypile;        
    
public:
    Pile();
    void addPiece(Piece* new_piece);
    string to_string();
};

#endif
