#include "../include/Table.hpp"


Chrono c_table(0,"microseconds");

using namespace std;


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

    // Initialise
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
                                //
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

void 
Table::instanciation(vector<Piece*> &mypile)
{
    int border_count=0,corner_count=0,insider_count=0;
    random_shuffle(mypile.begin(),mypile.end());
    pair<int,int> pair;
    for(Piece *p:mypile)
    {
        switch(p->borderCount())
        {
            case 2://corner
                pair=getCorner(corner_count);
                insertCorner(pair.first,pair.second,p);
                corner_count++;
                break;
            case 1://borderCount
                pair=getBorder(border_count);
                insertBorder(pair.first,pair.second,p);
                border_count++;
                break;
            case 0://insider
                pair=getInsider(insider_count);
                insertInsider(pair.first,pair.second,p);
                insider_count++;
                break;
        }
    }
}

Chrono
Table::test(vector<Piece*> &mypile)
{
    Chrono c(0,"milliseconds");
    c.start();    
    instanciation(mypile);
    c.stop();
    return c;
}


Chrono
Table::algoLocalSearch(vector<Piece*> &mypile)
{
    int degen_count=0,nonmdif_count=0;
    int saved_number_of_degen=1;
    int degen_max=10000,number_of_degen=saved_number_of_degen,nonmodif_max=5000;
    
    random_device rd;
    rng=mt19937(rd());    // random-number engine used (Mersenne-Twister in this case)
    uni_row=uniform_int_distribution<int>(0,rows_count-1); // guaranteed unbiased
    uni_column=uniform_int_distribution<int>(0,columns_count-1); // guaranteed unbiased
    
    instanciation(mypile);

    int min_error=getNumberOfAllError();;
    Chrono chrono(0,"milliseconds");
    chrono.start();
    
    int nb_errors=0;
    for(int i=0;i<rows_count;i++)
    {
        for(int j=0;j<columns_count;j++)
        {
            nb_errors+=numberOfErrors(i,j,mytable[i][j]);
        }
    }
    cout << "Il y a au début "<<nb_errors << endl;
    
    while(degen_count<=degen_max)
    {
        std::mt19937 rng(rd());
        if(degen_count<degen_max)
        {
            for(int i=0;i<number_of_degen;i++)
            {
                int initial_row=uni_row(rng);;
                int initial_column=uni_column(rng);
                PIECE_STATUS piece=getStatus(initial_row,initial_column);
                degeneration(initial_row,initial_column,piece,rng);
                cout << "Degen en cours" << endl;
            }
        }
        while(nonmdif_count<nonmodif_max)
        {
            for(int i=0;i<100 && nonmdif_count<nonmodif_max;i++)//on applique l'algo de base 100 fois
            {
                bool modif=false;
                int row;
                int column;
                int initial_row=uni_row(rng);;
                int initial_column=uni_column(rng);
                PIECE_STATUS piece=getStatus(initial_row,initial_column);
                int saved_error;
                pair<int,int> new_piece=getPieceForSearch(initial_row,initial_column,piece,rng,saved_error);
                if(new_piece.first==-1 && new_piece.second ==-1)
                {
                    modif=false;                
                }
                else
                {
                    modif=true;
                    row=new_piece.first;
                    column=new_piece.second;
                }
                
                if(modif==false)
                {
                    nonmdif_count++;
                }
                else
                {
                    //int nb_errors1=getNumberOfAllError();
                    
                    swap(initial_row,initial_column,row,column,piece);
                    
                    int nb_errors2=getNumberOfAllError();
                    if(nb_errors2<min_error)
                    {
                        min_error=nb_errors2;
                        cout << min_error << endl;
                    }
                    /*if(nb_errors1<nb_errors2)
                    {
                        cout << "erreur avant "<< nb_errors1 << ",erreurs après "<< nb_errors2 << " et pièce de type" << (int)piece << endl;
                        cout << "sur les pièces" << row <<","<< column << "|"<<initial_row<<","<<initial_column << endl;
                        if(isNeighbour(initial_row,initial_column,row,column))
                        {
                            cout << "voisin" << endl;
                        }
                    }*/
                }
                
            }
            int saved_error=getNumberOfAllError();
            bool modif=false;
            
            int row1,row2,column1,column2;
            for(int i=0;i<rows_count;i++)
            {
                for(int j=0;j<columns_count;j++)
                {
                    int error;
                    pair<int,int> new_piece=getPieceForSearch(i,j,getStatus(i,j),rng,error);
                    if(error>0)
                    {
                        if(error<saved_error)
                        {
                            row1=i;
                            column1=j;
                            row2=new_piece.first;
                            column2=new_piece.second;
                            modif=true;
                        }
                    }
                }
            }
            if(modif==true)
            {
                PIECE_STATUS piece=getStatus(row1,column1);
                int nb_errors1=getNumberOfAllError();
                        
                swap(row1,column1,row2,column2,getStatus(row1,column1));
                
                if(nb_errors2<min_error)
                {
                    min_error=nb_errors2;
                    cout << min_error << endl;
                }
                nonmdif_count=0;
            }
            
            
            
        }
        
        nonmdif_count=0;
        degen_count++;
    }
    cout << "min error "<< min_error<<endl;
    nb_errors=getNumberOfAllError();
    cout << "Il y a " << nb_errors<< "erreurs" <<endl;
    
    chrono.stop();
    
    return chrono;
}

pair<int,int>
Table::getCorner(int id)
{
    
    switch(id)
    {
        case 0:
            return make_pair<>(0,0);
        case 1:
            return make_pair<>(rows_count-1,0);
        case 2:
            return make_pair<>(0,columns_count-1);
        case 3:
            return make_pair<>(rows_count-1,columns_count-1);
        default:
            cerr<<"pas de "<< id <<" coin" <<endl;
    }
    return make_pair<>(0,0);
}

pair<int,int>
Table::getBorder(int id)
{
    int i=0,j=0;
    for(i=1;i<rows_count-1;i++)//parcours bord gauche
    {
        if(id==0)
        {
            //(mytable[i][j])->setRotation(0);
            return make_pair<>(i,j);
        }
        else
        {
            id--;
        }
    }
    i=rows_count-1;
    for(j=1;j<columns_count-1;j++)//parcours bord bas
    {
        if(id==0)
        {
            //(mytable[i][j])->setRotation(1);
            return make_pair<>(i,j);
        }
        else
        {
            id--;
        }
    }
    j=columns_count-1;
    for(i=rows_count-2;i>0;i--)//parcours bord droit
    {
        if(id==0)
        {
            //(mytable[i][j])->setRotation(2);
            return make_pair<>(i,j);
        }
        else
        {
            id--;
        }
    }
    i=0;
    for(j=columns_count-2;j>1;j--)//parcours bord haut
    {
        if(id==0)
        {
            //(mytable[i][j])->setRotation(3);
            return make_pair<>(i,j);
        }
        else
        {
            id--;
        }
    }
    if(id==0)
    {
        return make_pair<>(i,j);
    }
    
    cerr << "erreur dans le nombre de bord, il reste "<<id<<endl;
    return make_pair<>(-1,-1);
}

pair<int,int>
Table::getInsider(int id)
{
    for(int i=1;i<rows_count-1;i++)
    {
        for(int j=1;j<columns_count-1;j++)
        {
            if(id==0)
            {
                return make_pair<>(i,j);
            }
            else
            {
                id--;
            }
        }
    }
    cerr << "erreur dans le nombre d'intérieurs', il reste "<<id<<endl;
    return make_pair<>(-1,-1);
}

bool
Table::isNeighbour(int row1, int column1,int row2, int column2)
{
    bool res=false;
    if((row1-row2)==1 || (row1-row2)==-1)
    {
        if(column1==column2)
        {
            res=true;
        }
    }
    else if(row1==row2)
    {
        if((column2-column1)==1 || (column2-column1)==-1)
        {
            res=true;
        }
    }
    
    return res;
}


PIECE_STATUS 
Table::getStatus(int row, int column)
{
    PIECE_STATUS piece;
    if(row==0 || row == (rows_count-1))
    {
        if(column==0||column==columns_count-1)
        {
            piece=COIN;
        }
        else
        {
            piece=BORD;
        }
    }
    else if(column==0||column==columns_count-1)
    {
        piece=BORD;
    }
    else
    {
        piece=INTERIEUR;
    }
    return piece;
}

pair<int,int> 
Table::getPieceForSearch(int initial_row,int initial_column, PIECE_STATUS piece,std::mt19937 &rng, int &saved_error)
{
    saved_error=-1;
    int number_of_corners=4;
    int number_of_borders=(rows_count)*2+(columns_count)*2-8;
    int number_of_insiders=(rows_count)*(columns_count)-number_of_borders-number_of_corners;
    
    std::uniform_int_distribution<int> uni_corners(0,number_of_corners-1); // guaranteed unbiased
    std::uniform_int_distribution<int> uni_borders(0,number_of_borders-1); // guaranteed unbiased
    std::uniform_int_distribution<int> uni_insiders(0,number_of_insiders-1); // guaranteed unbiased
    
    pair <int,int> new_piece;
    int nb=0;
    switch(piece)
    {
        case COIN:
            nb=number_of_corners;
            break;
        case BORD:
            nb=number_of_borders;
            break;
        case INTERIEUR:
            nb=number_of_insiders;
            break;
    }
    int row=-1,column=-1;
    int error_count;
    for(int i=0;i<nb;i++)//On fait le nombre de swap nécessaire
    {
        switch(piece)
        {
            case COIN:
                new_piece=getCorner(uni_corners(rng));
                while(new_piece.first==initial_row && new_piece.second==initial_column)
                {
                    new_piece=getCorner(uni_corners(rng));
                }
                break;
            case BORD:
                new_piece=getBorder(uni_borders(rng));
                while(new_piece.first==initial_row && new_piece.second==initial_column)
                {
                    new_piece=getBorder(uni_borders(rng));
                }
                break;
            case INTERIEUR:
                new_piece=getInsider(uni_insiders(rng));
                if(number_of_insiders>1)
                {
                    while((new_piece.first==initial_row) && (new_piece.second==initial_column))
                    {
                        new_piece=getInsider(uni_insiders(rng));
                    }
                }
                break;
        }
        error_count=betterSwap(initial_row,initial_column,new_piece.first,new_piece.second,piece);
        if(error_count==-1)//si c'est un voisin neutre
        {
            row=new_piece.first;
            column=new_piece.second;
        }
        else if(error_count>=0)//si c'est un améliorant
        {
            saved_error=error_count;
            row=new_piece.first;
            column=new_piece.second;
            return make_pair<>(row,column);
        }
    }
    
    return make_pair<>(row,column);
}

int 
Table::getNumberOfAllError()
{
    int nb_errors=0;
    for(int i=0;i<rows_count;i++)
    {
        for(int j=0;j<columns_count;j++)
        {
            nb_errors+=numberOfErrors(i,j,mytable[i][j]);
        }
    }
    return nb_errors;
}


void 
Table::insertCorner(int row, int column,Piece* p)
{
    mytable[row][column]=p;
    p->setRotation(getBestRotation(row,column,p,COIN));
    
}

void 
Table::insertBorder(int row, int column,Piece* p)
{
    mytable[row][column]=p;
    p->setRotation(getBestRotation(row,column,p,BORD));
    
}

void 
Table::insertInsider(int row, int column,Piece* p)
{
    mytable[row][column]=p;
    p->setRotation(getBestRotation(row,column,p,INTERIEUR));
}

void
Table::swap(int row1, int column1, int row2, int column2,PIECE_STATUS piece)
{
    Piece *temp=mytable[row1][column1];
    switch(piece)
    {
        case COIN:
            insertCorner(row1,column1,mytable[row2][column2]);
            insertCorner(row2,column2,temp);
            break;
        case BORD:
            insertBorder(row1,column1,mytable[row2][column2]);
            insertBorder(row2,column2,temp);
            break;
        case INTERIEUR:
            if(isNeighbour(row1,column1,row2,column2))
            {
                int error_count;
                pair<int,int> best_rot=getBestRotationNeighbour(row1,column1,row2,column2,error_count,piece);
                mytable[row1][column1]->setRotation(best_rot.first);
                mytable[row2][column2]->setRotation(best_rot.second);

                mytable[row1][column1]=mytable[row2][column2];
                mytable[row2][column2]=temp;
                
            }
            else
            {
                insertInsider(row1,column1,mytable[row2][column2]);
                insertInsider(row2,column2,temp);
            }
            break;
    }
}


void 
Table::degeneration(int initial_row, int initial_column, PIECE_STATUS piece,std::mt19937 &rng)
{
    pair<int,int> new_piece;
    int number_of_corners=4;
    int number_of_borders=(rows_count)*2+(columns_count)*2-8;
    int number_of_insiders=(rows_count)*(columns_count)-number_of_borders-number_of_corners;
    
    std::uniform_int_distribution<int> uni_corners(0,number_of_corners-1); // guaranteed unbiased
    std::uniform_int_distribution<int> uni_borders(0,number_of_borders-1); // guaranteed unbiased
    std::uniform_int_distribution<int> uni_insiders(0,number_of_insiders-1); // guaranteed unbiased
    
    Piece *temp=mytable[initial_row][initial_column];
    switch(piece)
    {
        case COIN:
            new_piece=getCorner(uni_corners(rng));
            while(new_piece.first==initial_row && new_piece.second==initial_column)
            {
                new_piece=getCorner(uni_corners(rng));
            }
            insertCorner(initial_row,initial_column,mytable[new_piece.first][new_piece.second]);
            insertCorner(new_piece.first,new_piece.second,temp);
            break;
        case BORD:
            new_piece=getBorder(uni_borders(rng));
            while(new_piece.first==initial_row && new_piece.second==initial_column)
            {
                new_piece=getBorder(uni_borders(rng));
            }
            insertBorder(initial_row,initial_column,mytable[new_piece.first][new_piece.second]);
            insertBorder(new_piece.first,new_piece.second,temp);
            break;
        case INTERIEUR:
            new_piece=getInsider(uni_insiders(rng));
            if(number_of_insiders>1)
            {
                while((new_piece.first==initial_row) && (new_piece.second==initial_column))
                {
                    new_piece=getInsider(uni_insiders(rng));
                }
            }
            mytable[initial_row][initial_column]=mytable[new_piece.first][new_piece.second];
            mytable[new_piece.first][new_piece.second]=temp;
            break;
    }
    
}

int 
Table::getBestRotation(int row, int column,Piece* p,PIECE_STATUS piece)
{
    int best_rot=0;
    int min_error;
    int temp;
    int old_rotation=p->getRotation();
    switch(piece)
    {
        case INTERIEUR:
            min_error=numberOfErrors(row,column,p);
            for(int i=1;i<4;i++)
            {
                p->rotation();
                temp=numberOfErrors(row,column,p);
                if(min_error>temp)
                {
                    best_rot=i;
                    min_error=temp;
                }
            }
            break;
            
        case COIN:
            if(row==0)
            {
                if(column==0)
                {
                    while(p->getColor(HAUT)!=0 || p->getColor(GAUCHE)!=0)
                    {
                        p->rotation();
                    }
                }
                else
                {
                    while(p->getColor(HAUT)!=0 || p->getColor(DROITE)!=0)
                    {
                        p->rotation();
                    }
                }
            }
            else
            {
                if(column==0)
                {
                    while(p->getColor(BAS)!=0 || p->getColor(GAUCHE)!=0)
                    {
                        p->rotation();
                    }
                }
                else
                {
                    while(p->getColor(BAS)!=0 || p->getColor(DROITE)!=0)
                    {
                        p->rotation();
                    }
                }
            }
            break;
            
        case BORD:
            if(row==0)
            {
                while(p->getColor(HAUT)!=0)
                {
                    p->rotation();
                }
            }
            else if(row==rows_count-1)
            {
                while(p->getColor(BAS)!=0)
                {
                    p->rotation();
                }
            }
            else if(column==0)
            {
                while(p->getColor(GAUCHE)!=0)
                {
                    p->rotation();
                }
            }
            else
            {
                while(p->getColor(DROITE)!=0)
                {
                    p->rotation();
                }
            }
            break;
    }
    best_rot=p->getRotation();
    p->setRotation(old_rotation);
    
    return best_rot;
}

pair<int,int> 
Table::getBestRotationNeighbour(int row1, int column1,int row2, int column2,int &error,PIECE_STATUS piece)
{
    int old_rot1=mytable[row1][column1]->getRotation();
    int old_rot2=mytable[row2][column2]->getRotation();
    
    Piece* temp=mytable[row1][column1];
    mytable[row1][column1]=mytable[row2][column2];
    mytable[row2][column2]=temp;
    
    int best_rot1,best_rot2;
    error=9;//max number of errors +1
    //numberOfErrors(row2,column2,mytable[row2][column2],best_rot2)+numberOfErrors(row1,column1,mytable[row1][column1],best_rot1);
    
    switch(piece)
    {
        case INTERIEUR:
            
            for(int rot1=0;rot1<4;rot1++)
            {
                mytable[row1][column1]->setRotation(rot1);
                for(int rot2=0;rot2<4;rot2++)
                {
                    mytable[row2][column2]->setRotation(rot2);
                    int error_actual=numberOfErrors(row1,column1,mytable[row1][column1])+numberOfErrors(row2,column2,mytable[row2][column2]);
                    if(error>error_actual)
                    {
                        error=error_actual;
                        best_rot1=rot1;
                        best_rot2=rot2;
                    }
                }
            }
            break;
        case BORD:
            mytable[row1][column1]->setRotation(getBestRotation(row1,column1,mytable[row1][column1],piece));
            mytable[row2][column2]->setRotation(getBestRotation(row2,column2,mytable[row2][column2],piece));
            
            error=numberOfErrors(row1,column1,mytable[row1][column1])+numberOfErrors(row2,column2,mytable[row2][column2]);
            
            break;
        case COIN :
                cerr << "Pas de coin ici "<< endl;
            break;
    }
    
    temp=mytable[row1][column1];
    mytable[row1][column1]=mytable[row2][column2];
    mytable[row2][column2]=temp;
    
    mytable[row1][column1]->setRotation(old_rot1);
    mytable[row2][column2]->setRotation(old_rot2);
    
    return make_pair<>(best_rot2,best_rot1);
}



int 
Table::numberOfErrors(int row, int column,Piece* p,int rotation)
{
    int old_rotation=p->getRotation();
    if(rotation!=-1)
    {
        p->setRotation(rotation);
    }
    int count=0;
    int* tab_color=p->getAllColor();
    //on doit vérifier que le dessus s'il est en bas
    if(row==0)//on vérifie en haut
    {
        if(((mytable[row+1][column]))!=nullptr)
        {
            int pBAS=tab_color[BAS];
            if(pBAS != ((mytable[row+1][column]))->getColor(HAUT))//on vérifie en bas
            {
                count++;
            }
        }
    }
    else if(row==(rows_count-1))//on vérifie en bas
    {
        if(((mytable[row-1][column]))!=nullptr)
        {
            int pHAUT=tab_color[HAUT];
            if(pHAUT != ((mytable[row-1][column]))->getColor(BAS))//on vérifie en haut
            {
                count++;
            }
        }
    }
    else
    {
        if(((mytable[row-1][column]))!=nullptr)
        {
            int pHAUT=tab_color[HAUT];
            if(pHAUT != ((mytable[row-1][column]))->getColor(BAS))//on vérifie en haut
            {
                count++;
            }
        }
        if(((mytable[row+1][column]))!=nullptr)
        {
            int pBAS=tab_color[BAS];
            if(pBAS != ((mytable[row+1][column]))->getColor(HAUT))//on vérifie en bas
            {
                count++;
            }
        }
    }
        
    if(column==0)
    {
        if(((mytable[row][column+1]))!=nullptr)
        {
            int pDROITE=tab_color[DROITE];
            if(pDROITE != ((mytable[row][column+1]))->getColor(GAUCHE))
            {
                count++;
            }
        }
        
    }
    else if(column==(columns_count-1))
    {
        if(((mytable[row][column-1]))!=nullptr)
        {
            int pGAUCHE=tab_color[GAUCHE];
            if(pGAUCHE != ((mytable[row][column-1]))->getColor(DROITE))
            {
                count++;
            }
        }
        
    }
    else
    {
        if(((mytable[row][column-1]))!=nullptr)
        {
            int pGAUCHE=tab_color[GAUCHE];
            if(pGAUCHE != ((mytable[row][column-1]))->getColor(DROITE))
            {
                count++;
            }
        }
        if(((mytable[row][column+1]))!=nullptr)
        {
            int pDROITE=tab_color[DROITE];
            if(pDROITE != ((mytable[row][column+1]))->getColor(GAUCHE))
            {
                count++;
            }
        }
    }
    p->setRotation(old_rotation);
    return count;
}




int 
Table::betterSwap(int row1, int column1, int row2, int column2,PIECE_STATUS piece)
{
    int res;
    int error_count;
    if(isNeighbour(row1,column1,row2,column2))
    {
        getBestRotationNeighbour(row1,column1,row2,column2,error_count,piece);
    }
    else
    {
        int value1,value2;
        value1=getBestRotation(row1,column1,mytable[row2][column2],piece);
        value2=getBestRotation(row2,column2,mytable[row1][column1],piece);
        
        error_count=numberOfErrors(row1,column1,mytable[row2][column2],value1)+numberOfErrors(row2,column2,mytable[row1][column1],value2);
    }
    if( error_count
        <
        (numberOfErrors(row1,column1,mytable[row1][column1])+numberOfErrors(row2,column2,mytable[row2][column2])))
    {
        res=error_count;
    }
    else if( error_count
        ==
        (numberOfErrors(row1,column1,mytable[row1][column1])+numberOfErrors(row2,column2,mytable[row2][column2])) && !isNeighbour(row1,column1,row2,column2))
    {
        res=-1;
    }
    else
    {
        res=-2;
    }
    
    return res;
    
}































