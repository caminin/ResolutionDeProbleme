#include "../include/Table.hpp"


Chrono c_table(0,"microseconds");


Table::Table(int _rows_count,int _columns_count) : rows_count(_rows_count),columns_count(_columns_count)
{
    mytable.resize(_rows_count,vector<pair<Piece*,int> >(_columns_count,make_pair<>(nullptr,0)));
}


void
Table::addPiece(int row, int column,pair<Piece*,int> p)
{
    mytable[row][column]=p;
}

void
Table::removePiece(int row, int column)
{
   get<0>(mytable[row][column])=nullptr;
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
        else if((get<0>(mytable[row+1][column]))!=nullptr)
        {
            if(pBAS != (get<0>(mytable[row+1][column]))->getColor1(HAUT))//on vérifie en bas
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
        else if((get<0>(mytable[row-1][column]))!=nullptr)
        {
            if(pHAUT != (get<0>(mytable[row-1][column]))->getColor1(BAS))//on vérifie en haut
            {
                return false;
            }
        }
    }
    else
    {
        if((get<0>(mytable[row-1][column]))!=nullptr)
        {
            if(pHAUT != (get<0>(mytable[row-1][column]))->getColor1(BAS))//on vérifie en haut
            {
                return false;
            }
        }
        if((get<0>(mytable[row+1][column]))!=nullptr)
        {
            if(pBAS != (get<0>(mytable[row+1][column]))->getColor1(HAUT))//on vérifie en bas
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
        else if((get<0>(mytable[row][column+1]))!=nullptr)
        {
            if(pDROITE != (get<0>(mytable[row][column+1]))->getColor1(GAUCHE))
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
        else if((get<0>(mytable[row][column-1]))!=nullptr)
        {
            if(pGAUCHE != (get<0>(mytable[row][column-1]))->getColor1(DROITE))
            {
                return false;
            }
        }
        
    }
    else
    {
        if((get<0>(mytable[row][column-1]))!=nullptr)
        {
            if(pGAUCHE != (get<0>(mytable[row][column-1]))->getColor1(DROITE))
            {
                return false;
            }
        }
        if((get<0>(mytable[row][column+1]))!=nullptr)
        {
            if(pDROITE != (get<0>(mytable[row][column+1]))->getColor1(GAUCHE))
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
            if((get<0>(mytable[i][j]))!=nullptr)
            {
                //cout << get<1>(mytable[i][j])<< endl;
                get<0>(mytable[i][j])->setRotation(get<1>(mytable[i][j]));
                cout << (get<0>(mytable[i][j]))->to_string() << "|";
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
            //cout << "Case("<<i<<","<<j<<") : "<<(get<0>(mytable[i][j]))->getId() << " Rotation :" << (get<0>(mytable[i][j]))->getRotation() << endl;
            cout <<(get<0>(mytable[i][j]))->getId() << " " << (get<0>(mytable[i][j]))->getRotation() << endl;
        }
    }

}

void 
Table::rotate(int row, int column)
{
    (get<0>(mytable[row][column]))->rotation();
}



Chrono
Table::algoCSP(vector<Piece*> &mypile)
{
    vector< pair<Piece*,int> > pile_rec;
    vector< pair<int,int> > coord;
    pair<Piece*,int> piece;
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
                pile_rec.push_back(make_pair<>(p,p->getRotation()));
                coord.push_back(coord_actual);
            }
        }
    }
    
    while(pile_rec.size()>0 && end==false)
    {
        //cout << pile_rec.size() << endl;
        piece=pile_rec.back();
        pile_rec.pop_back();
        
        coord_actual=coord.back();
        coord.pop_back();
        c_row=get<0>(coord_actual);
        c_column=get<1>(coord_actual);
        
        addPiece(c_row,c_column,piece);
        for(i=0;i<rows_count;i++)
        {
            for(j=0;j<columns_count;j++)
            {
                if((get<0>(mytable[i][j]))!=nullptr)
                {
                    get<0>(mytable[i][j])->setRotation(get<1>(mytable[i][j]));
                }
            }
        }
        
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
            while(get<0>(mytable[i][j])!=nullptr)
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
                        for(vector< pair<Piece*,int> > v:mytable)
                        {
                            for(pair<Piece*,int>p2:v)
                            {
                                if(get<0>(p2)!=nullptr)
                                {
                                    if(*get<0>(p2)==*p)
                                    {
                                        identical=true;
                                    }
                                }
                            }
                        }
                        if(identical==false)
                        {
                            pile_rec.push_back(make_pair<>(p,p->getRotation()));
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

