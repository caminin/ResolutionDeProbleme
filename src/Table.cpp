#include "../include/Table.hpp"


Chrono c_table(0,"microseconds");


Table::Table(int _rows_count,int _columns_count) : rows_count(_rows_count),columns_count(_columns_count)
{
    mytable.resize(_rows_count,vector<Piece*>(_columns_count,nullptr));
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
    int pHAUT=p->getColor1(HAUT);
    int pBAS=p->getColor1(BAS);
    int pGAUCHE=p->getColor1(GAUCHE);
    int pDROITE=p->getColor1(DROITE);
    //on doit vérifier que le dessus s'ilest en bas
    if(row==0)//on vérifie en haut
    {
        if(pHAUT!=0)
        {
            return false;
        }
        else if(((mytable[row+1][column]))!=nullptr)
        {
            if(pBAS != ((mytable[row+1][column]))->getColor1(HAUT))//on vérifie en bas
            {
                return false;
            }
        }
    }
    else if(row==(rows_count-1))//on vérifie en bas
    {
        if(pBAS!=0)
        {
            return false;
        }
        else if(((mytable[row-1][column]))!=nullptr)
        {
            if(pHAUT != ((mytable[row-1][column]))->getColor1(BAS))//on vérifie en haut
            {
                return false;
            }
        }
    }
    else
    {
        if(((mytable[row-1][column]))!=nullptr)
        {
            if(pHAUT != ((mytable[row-1][column]))->getColor1(BAS))//on vérifie en haut
            {
                return false;
            }
        }
        if(((mytable[row+1][column]))!=nullptr)
        {
            if(pBAS != ((mytable[row+1][column]))->getColor1(HAUT))//on vérifie en bas
            {
                return false;
            }
        }
    }
        

    if(column==0)
    {
        if(pGAUCHE!=0)
        {
            return false;
        }
        else if(((mytable[row][column+1]))!=nullptr)
        {
            if(pDROITE != ((mytable[row][column+1]))->getColor1(GAUCHE))
            {
                return false;
            }
        }
        
    }
    else if(column==(columns_count-1))
    {
        if(pDROITE!=0)
        {
            return false;
        }
        else if(((mytable[row][column-1]))!=nullptr)
        {
            if(pGAUCHE != ((mytable[row][column-1]))->getColor1(DROITE))
            {
                return false;
            }
        }
        
    }
    else
    {
        if(((mytable[row][column-1]))!=nullptr)
        {
            if(pGAUCHE != ((mytable[row][column-1]))->getColor1(DROITE))
            {
                return false;
            }
        }
        if(((mytable[row][column+1]))!=nullptr)
        {
            if(pDROITE != ((mytable[row][column+1]))->getColor1(GAUCHE))
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
                i=c_row;
                j=c_column;
                while((mytable[i][j])!=nullptr)
                {
                    removePiece(i,j);
                    j++;
                    if(j>=columns_count)
                    {
                        i++;
                        j=0;
                    }
                }
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
                            }
                        }
                    }
                }
            }
        }
        else
        {
            while((mytable[c_row][c_column])!=nullptr)
            {
                removePiece(c_row,c_column);
                ++c_column;
                if(c_column>=columns_count)
                {
                    c_row++;
                    c_column=0;
                }
            }
        }
        
        
    }
    
    chrono.stop();
    return chrono;
}

