#include "../include/Piece.hpp"

int Piece::id_all=0;

Piece::Piece(vector<int> _color, int _rotation)
{
    id=Piece::id_all;
    Piece::id_all++;
    myrotation=_rotation;
    placed=false;
    
    index_tab_color=new int*[4];
    for(int i=0;i<4;i++)
    {
        index_tab_color[i]=new int[4];
    }
    
    int index=0;
    for(int c:_color)
    {
       index_tab_color[0][index]=c;
       index=((index==3)?0:++index);
       index_tab_color[1][index]=c;
       index=((index==3)?0:++index);
       index_tab_color[2][index]=c;
       index=((index==3)?0:++index);
       index_tab_color[3][index]=c;
       index=((index==3)?0:++index);
       
       index=((index==3)?0:++index);
    }
    mycolor=index_tab_color[BAS];
}


void
Piece::setRotation(int new_rotation)
{
    while(myrotation!=new_rotation)
    {
        rotation();
    }
}


void
Piece::rotation()
{
    if(myrotation==3)
    {
        myrotation=0;
    }
    else
    {
        ++myrotation;
    }
    mycolor=index_tab_color[myrotation];
}


int 
Piece::getColor(int face)
{
    return mycolor[face];  
}

int*
Piece::getAllColor()
{
    return mycolor;
}


string
Piece::to_string()
{
    string res="Pièce de couleur "+std::to_string(mycolor[0])+"/"+std::to_string(mycolor[1])+"/"+std::to_string(mycolor[2])+"/"+std::to_string(mycolor[3]);
    
    return res;
}

int
Piece::borderCount()
{
    int nb=0;
    for(int i=0;i<4;i++)
    {
        if(getColor(i)==0)
        {
            nb++;
        }
    }
    return nb;
}

bool
Piece::operator==(Piece p1)
{
    bool res;
    if(id==p1.id)
    {
        res=true;
    }
    else
    {
        res=false;
    }
    
    return res;
}
