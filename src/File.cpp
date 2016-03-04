#include "../include/File.hpp"

using namespace std;

vector<int> &split(const string &s, char delim, vector<int> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(stoi(item,0));
    }
    return elems;
}


vector<int> split(const string &s, char delim) {
    vector<int> elems;
    split(s, delim, elems);
    return elems;
}


void parseFile(Table *mytable, vector<Piece*> &mypile,string file_name)
{
    ifstream file(file_name.c_str());
    if (file.is_open())
    {		
        string first_line;
        getline(file,first_line);
        vector<int> tab_line=split(first_line,' ');
        if(tab_line.size()!=2)
        {
            cerr << "Le fichier est mal formatté" << endl;
        }
        else
        {
            //On récupère le nombre de lignes et colonnes
            int rows_count=tab_line[1];
            int columns_count=tab_line[0];
            
            cout << "row : " << rows_count <<" and columns : " << columns_count << endl;
            *mytable=Table(rows_count,columns_count);
            
        }
        
        string line;
        while(getline(file,line))
        {
            tab_line=split(line,' ');
            if(tab_line.size()!=4)
            {
                cerr << "Le fichier est mal formatté" << endl;
            }
            else
            {
                mypile.insert(mypile.begin(),new Piece(tab_line,BAS));
            }
        }
        
	    file.close();
        
        #ifdef DEBUG
            printf("Je sors de la lecture\n");
            cout << mypile.size() << endl;
        #endif
    }
    else
    {
      // On affiche un message d'erreur si on veut
      cerr<< "Impossible d'ouvrir le fichier \n"<<endl;
    }
}
