#include "../include/Piece.hpp"

int Piece::id_all=0;

Piece::Piece(vector<int> _color, int _rotation)
{
    id=Piece::id_all;
    Piece::id_all++;
    mycolor=_color;
    myrotation=_rotation;
}


void
Piece::setRotation(int new_rotation)
{
    while(myrotation!=new_rotation)
    {
        rotation();
    }
}


bool
Piece::isInside(vector<  vector<pair<Piece*,int > > > &mytable)
{
    for(vector< pair<Piece*,int> > v:mytable)
    {
        for(pair<Piece*,int>p2:v)
        {
            if(get<0>(p2)!=nullptr)
            {
                if(*get<0>(p2)==*this)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

void
Piece::rotation()
{
    rotation1();
}


void Piece::rotation1()
{
    if(myrotation==3)
    {
        myrotation=0;
    }
    else
    {
        myrotation++;
    }
    int temp=mycolor[3];
    mycolor.insert(mycolor.begin(),temp);
    mycolor.pop_back();
    
}

void Piece::rotation2()
{
    if(myrotation==3)
    {
        myrotation=0;
    }
}

int 
Piece::getColor(Face face)
{
    return getColor1(face);    
}


int Piece::getColor1(Face face)
{
    return mycolor[face];
}

int Piece::getColor2(Face face)
{
    return 0;
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
