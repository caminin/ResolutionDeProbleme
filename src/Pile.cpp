#include "../include/Pile.hpp"

Pile::Pile()
{
    
}

    
    
void 
Pile::addPiece(Piece* new_piece)
{
    mypile.push_back(new_piece);
}

string
Pile::to_string()
{
    string res;
    for(Piece* p:mypile)
    {
        res+=(p->to_string()+"\n");
    }
    
    return res;
}


