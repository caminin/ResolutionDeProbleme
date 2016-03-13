#include "../include/Piece.hpp"

int Piece::id_all=0;

Piece::Piece(vector<int> _color, int _rotation)
{
    id=Piece::id_all;
    Piece::id_all++;
    myrotation=_rotation;
    placed=false;
    
    index_tab=new int*[4];
    for(int i=0;i<4;i++)
    {
        index_tab[i]=new int[4];
    }
    
    int index=0;
    for(int c:_color)
    {
       index_tab[0][index]=c;
       index=((index==3)?0:++index);
       index_tab[1][index]=c;
       index=((index==3)?0:++index);
       index_tab[2][index]=c;
       index=((index==3)?0:++index);
       index_tab[3][index]=c;
       index=((index==3)?0:++index);
       
       index=((index==3)?0:++index);
    }
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
    /*int temp=mycolor[3];
    mycolor[3]=mycolor[2];
    mycolor[2]=mycolor[1];
    mycolor[1]=mycolor[0];
    mycolor[0]=temp;*/
    mycolor=index_tab[myrotation];
}


int 
Piece::getColor(int face)
{
    return mycolor[face];  
}


string
Piece::to_string()
{
    string res="Pièce de couleur "+std::to_string(mycolor[0])+"/"+std::to_string(mycolor[1])+"/"+std::to_string(mycolor[2])+"/"+std::to_string(mycolor[3]);
    
    return res;
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
