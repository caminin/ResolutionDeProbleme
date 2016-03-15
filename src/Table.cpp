#include "../include/Table.hpp"


Chrono c_table(0,"microseconds");


Table::Table(int _rows_count,int _columns_count) : rows_count(_rows_count),columns_count(_columns_count)
{
    mytable=new Piece**[rows_count];    
    for(int i=0;i<rows_count;i++)
    {
        mytable[i]=new Piece*[columns_count];
        for(int j=0;j<columns_count;j++)
        {
            mytable[i][j]=nullptr;
        }
    }
    mytable_rotation.resize(_rows_count,vector<int>(_columns_count,BAS));
}


void
Table::addPiece(int row, int column,Piece* p, int rot)
{
    if(mytable[row][column]!=nullptr)
    {
        mytable[row][column]->setUnplaced();
    }
    mytable[row][column]=p;
    p->setPlaced();
    p->setRotation(rot);
}

void
Table::removePiece(int row, int column)
{
    if(mytable[row][column]!=nullptr)
    {
        mytable[row][column]->setUnplaced();
        mytable[row][column]=nullptr;
        mytable_rotation[row][column]=BAS;
    }
}



bool 
Table::checkPiece(int row, int column,Piece *p)
{
    //on doit vérifier que le dessus s'il est en bas
    if(row==0)//on vérifie en haut
    {
        int pHAUT=p->getColor(HAUT);
        if(pHAUT!=0)
        {
            return false;
        }
        else if(((mytable[row+1][column]))!=nullptr)
        {
            int pBAS=p->getColor(BAS);
            if(pBAS != ((mytable[row+1][column]))->getColor(HAUT))//on vérifie en bas
            {
                return false;
            }
        }
    }
    else if(row==(rows_count-1))//on vérifie en bas
    {
        int pBAS=p->getColor(BAS);
        if(pBAS!=0)
        {
            return false;
        }
        else if(((mytable[row-1][column]))!=nullptr)
        {
            int pHAUT=p->getColor(HAUT);
            if(pHAUT != ((mytable[row-1][column]))->getColor(BAS))//on vérifie en haut
            {
                return false;
            }
        }
    }
    else
    {
        if(((mytable[row-1][column]))!=nullptr)
        {
            int pHAUT=p->getColor(HAUT);
            if(pHAUT != ((mytable[row-1][column]))->getColor(BAS))//on vérifie en haut
            {
                return false;
            }
        }
        if(((mytable[row+1][column]))!=nullptr)
        {
            int pBAS=p->getColor(BAS);
            if(pBAS != ((mytable[row+1][column]))->getColor(HAUT))//on vérifie en bas
            {
                return false;
            }
        }
    }
        
    
    
    if(column==0)
    {
        int pGAUCHE=p->getColor(GAUCHE);
        if(pGAUCHE!=0)
        {
            return false;
        }
        else if(((mytable[row][column+1]))!=nullptr)
        {
            int pDROITE=p->getColor(DROITE);
            if(pDROITE != ((mytable[row][column+1]))->getColor(GAUCHE))
            {
                return false;
            }
        }
        
    }
    else if(column==(columns_count-1))
    {
        int pDROITE=p->getColor(DROITE);
        if(pDROITE!=0)
        {
            return false;
        }
        else if(((mytable[row][column-1]))!=nullptr)
        {
            int pGAUCHE=p->getColor(GAUCHE);
            if(pGAUCHE != ((mytable[row][column-1]))->getColor(DROITE))
            {
                return false;
            }
        }
        
    }
    else
    {
        if(((mytable[row][column-1]))!=nullptr)
        {
            int pGAUCHE=p->getColor(GAUCHE);
            if(pGAUCHE != ((mytable[row][column-1]))->getColor(DROITE))
            {
                return false;
            }
        }
        if(((mytable[row][column+1]))!=nullptr)
        {
            int pDROITE=p->getColor(DROITE);
            if(pDROITE != ((mytable[row][column+1]))->getColor(GAUCHE))
            {
                return false;
            }
        }
    }
    return true;
}

void
Table::showTable()
{
    for(int i=0;i<rows_count;i++)
    {
        for(int j=0;j<columns_count;j++)
        {
            if(((mytable[i][j]))!=nullptr)
            {
                cout << ((mytable[i][j]))->to_string() << "|";
            }
            else
            {
                cout << "########################|";
            }
        }
        cout << endl;
    }
}

void
Table::getRes(string row, string column)
{
    string s("./sol/sol_"+row+"_"+column+".txt");
    ofstream fichier(s.c_str(), ios::out| ios::trunc);

    for(int i=0;i<rows_count;i++)
    {
        for(int j=0;j<columns_count;j++)
        {
            fichier <<(mytable[i][j])->getId() << " " << (mytable[i][j])->getRotation() << endl;
        }
    }

}

void 
Table::rotate(int row, int column)
{
    ((mytable[row][column]))->rotation();
}

Piece* 
Table::getCorner(int id)
{
    Piece* p=nullptr;
    switch(id)
    {
        case 0:
            p=mytable[0][0];
            break;
        case 1:
            p=mytable[rows_count-1][0];
            break;
        case 2:
            p=mytable[0][columns_count-1];
            break;
        case 3:
            p=mytable[rows_count-1][columns_count-1];
            break;
        default:
            cerr<<"pas de "<< id <<" coin"
    }
    
    return p;
}

Piece* 
Table::getBorder(int id)
{
    int i=0,j=0;
    for(i=1;i<rows_count-1;i++)//parcours bord gauche
    {
        if(id==0)
        {
            return mytable[i][j];
        }
        else
        {
            id--;
        }
    }
    for(i=rows_count-2,j=1;j<columns_count-1;j++)//parcours bord bas
    {
        if(id==0)
        {
            return mytable[i][j];
        }
        else
        {
            id--;
        }
    }
    for(i=rows_count-2,j=columns_count-2;i>0;i--)//parcours bord droit
    {
        if(id==0)
        {
            return mytable[i][j];
        }
        else
        {
            id--;
        }
    }
    for(i=1,j=columns_count-2;j>1;j--)//parcours bord haut
    {
        if(id==0)
        {
            return mytable[i][j];
        }
        else
        {
            id--;
        }
    }
    
    cerr << "erreur dans le nombre de bord, il reste "<<id<<endl;
    return nullptr;
}

Piece* 
Table::getInsider(int id)
{
    for(int i=1;i<rows_count-2;i++)
    {
        for(int j=1;j<columns_count-2;j++)
        {
            if(id==0)
            {
                return mytable[i][j];
            }
            else
            {
                id--;
            }
        }
    }
    cerr << "erreur dans le nombre d'intérieurs', il reste "<<id<<endl;
    return nullptr;
}

void 
Table::instanciation(vector<Piece*> &mypile)
{
    int border_count=0,corner_count=0,insider_count=0;
    random_shuffle(mypile.begin(),mypile.end());
    for(Piece *p:mypile)
    {
        switch(p->borderCount())
        {
            case 2://corner
                getCorner(corner_count)=p;
                corner_count++;
                break;
            case 1://borderCount
                getBorder(borderCount)=p;
                borderCount++;
                break;
            case 0://insider
                getInsider(insider_count)=p;
                insider_count++;
                break;
        }
    }
}


Chrono
Table::algoLocalSearch(vector<Piece*> &mypile)
{
    int corner_count=0;
    int border_count=0;
    int piece_count=0;
    
    Chrono chrono(0,"milliseconds");
    chrono.start();
    
    instanciation(mypile);
    
    chrono.stop();
    
    return chrono;
}



Chrono
Table::algoCSP(vector<Piece*> &mypile)
{
    vector< Piece* > pile_rec;
    vector <int> rot_rec;
    
    vector< int > coord_x;
    vector< int > coord_y;
    Piece* piece;
    int rot;
    bool end=false;
    bool needRemove=false;
    
    int c_row,c_column,i,j;
    
    Chrono chrono(0,"milliseconds");
    chrono.start();

    for(Piece *p:mypile)
    {
        for(int i=0;i<4;i++)
        {
            p->rotation();
            if(checkPiece(0,0,p))
            {
                pile_rec.push_back(p);
                rot_rec.push_back(p->getRotation());
                coord_x.push_back(0);
                coord_y.push_back(0);
            }
        }
    }
    
    while(pile_rec.size()>0 && end==false)
    {
        piece=pile_rec.back();
        pile_rec.pop_back();
        
        rot=rot_rec.back();
        rot_rec.pop_back();
        
        c_row=coord_x.back();
        coord_x.pop_back();
        
        c_column=coord_y.back();
        coord_y.pop_back();
        int nb=0;
        
        i=c_row;
        j=c_column;
        while((mytable[i][j])!=nullptr)
        {
            removePiece(i,j);
            j++;
            if(j>=columns_count)
            {
                j=0;
                ++i;
            }
        }
        
        if(piece->getPlaced()==false)
        {
            addPiece(c_row,c_column,piece,rot);
            
            ++c_column;
            
            if(c_column>=columns_count)
            {
                c_column=0;
                ++c_row;
                
                if(c_row>=rows_count)
                {
                    end=true;
                }
            }
            
            if(end==false)
            {
                
                for(Piece *p:mypile)
                {
                    if(p->getPlaced()==false)
                    {
                        for(i=0;i<4;i++)
                        {
                            p->rotation();
                            if(checkPiece(c_row,c_column,p))
                            {
                                pile_rec.push_back(p);
                                rot_rec.push_back(p->getRotation());
                                coord_x.push_back(c_row);
                                coord_y.push_back(c_column);
                                if(mytable[2][0]!=nullptr && nb>11)
                                {
                                    if(mytable[2][0]->getId()==8&&mytable[2][0]->getRotation()==1)
                                    {
                                        cout << p->to_string() <<"|"<<p->getId()<<"|" << p->getRotation() << endl;
                                    }
                                    cout << endl;
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(mytable[c_row][c_column]->getId()==piece->getId())
            {
                piece->setRotation(rot);

            }
            ++c_column;
            
            if(c_column>=columns_count)
            {
                c_column=0;
                ++c_row;
                
                if(c_row<rows_count)
                {
                    needRemove=true;
                }
            }
            else
            {
                needRemove=true; 
            }
            
            if(needRemove==true)
            {
                while((mytable[c_row][c_column])!=nullptr)
                {
                    removePiece(c_row,c_column);
                    ++c_column;
                    if(c_column>=columns_count)
                    {
                        c_column=0;
                        ++c_row;
                    }
                }
                
            }
        }
        
        
    }
    
    chrono.stop();
    return chrono;
}

