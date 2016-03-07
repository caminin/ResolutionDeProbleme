#include "../include/Table.hpp"


Chrono c_table(0,"microseconds");


Table::Table(int _rows_count,int _columns_count) : rows_count(_rows_count),columns_count(_columns_count)
{
    mytable.resize(_rows_count,vector<Piece* >(_columns_count,nullptr));
}


void
Table::addPiece(int row, int column,Piece* p)
{
    mytable[row][column]=p;
}

void
Table::removePiece(int row, int column)
{
   mytable[row][column]=nullptr;
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
        else if((mytable[row+1][column])!=nullptr)
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
                //cout << (mytable[i][j])<< endl;
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
Table::getRes()
{
    for(int i=0;i<rows_count;i++)
    {
        for(int j=0;j<columns_count;j++)
        {
            //cout << "Case("<<i<<","<<j<<") : "<<((mytable[i][j]))->getId() << " Rotation :" << ((mytable[i][j]))->getRotation() << endl;
            cout <<((mytable[i][j]))->getId() << " " << ((mytable[i][j]))->getRotation() << endl;
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
    //vector< pair<Piece*,int> > pile_rec;
    list<Piece*> pile_rec_p;
    list<int> pile_rec_r;
    
    vector< pair<int,int> > coord;
    Piece* piece;
    int rot;
    bool identical;
    int c_row,c_column,i,j;
    pair<int,int> coord_actual=make_pair(0,0);
    Chrono chrono(0,"milliseconds");
    chrono.start();
    bool end=false;

    for(Piece *p:mypile)
    {
        for(int i=0;i<4;i++)
        {
            p->rotation();
            if(checkPiece(0,0,p))
            {
                pile_rec_p.push_front(p);
                pile_rec_r.push_front(p->getRotation());
                coord.push_back(coord_actual);
            }
        }
    }
    
    while(pile_rec_p.size()>0 && end==false)
    {
        //cout << pile_rec.size() << endl;
        piece=pile_rec_p.front();
        rot=pile_rec_r.front();
        pile_rec_p.pop_front();
        pile_rec_r.pop_front();
        
        coord_actual=coord.back();
        coord.pop_back();
        c_row=get<0>(coord_actual);
        c_column=get<1>(coord_actual);
        
        
        piece->setRotation(rot);
        addPiece(c_row,c_column,piece);
        
        
        if(c_column==columns_count-1)
        {
            c_column=0;
            if(c_row==rows_count-1)
            {
                end=true;
            }
            else
            {
                c_row++;
            }
        }
        else
        {
            c_column++;
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
                
                for(i=0;i<4;i++)
                {
                    p->rotation();
                    if(checkPiece(c_row,c_column,p))
                    {
                        identical=false;
                        for(vector< Piece*> v:mytable)
                        {
                            for(Piece* p2:v)
                            {
                                if(p2!=nullptr)
                                {
                                    if(*p2==*p)
                                    {
                                        identical=true;
                                    }
                                }
                            }
                        }
                        if(identical==false)
                        {
                            pile_rec_p.push_front(p);
                            pile_rec_r.push_front(p->getRotation());
                            coord.push_back(make_pair<>(c_row,c_column));
                        }
                    }
                }
            }
        }
        
        
    }
    
    chrono.stop();
    return chrono;
}
