#ifndef __MYCASE
#define __MYCASE

#include <vector>

using namespace std;

enum Rotation{BAS,GAUCHE,HAUT,DROITE};

class Case
{
    Rotation myrotation;
    vector<int> color;

    void rotation1();
    void rotation2();
    
    int getColor1(int face);
    int getColor2(int face);
    
    
};






#endif
