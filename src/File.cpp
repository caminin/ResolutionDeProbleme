#include "../include/File.hpp"

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


void parseFile(string file_name)
{
    ifstream file(file_name.c_str());
    if (file.is_open())
    {		
        string first_line;
        getline(file,first_line);
        vector<string> tab_line=split(first_line,' ');
        if(tab_line.size()!=2)
        {
            cerr << "Le fichier est mal formatté" << endl;
        }
        else
        {
            //On récupère le nombre de lignes et colonnes
            int line_count=stoi(tab_line[0],0);
            int row_count=stoi(tab_line[1],0);
            
            cout << "line : " << line_count <<" and row : " << row_count << endl;
            
        }
        
        string line;
        while(getline(file,line))
        {
            cout << line << endl;
        }
	    file.close();
        
        #ifdef DEBUG
            printf("Je sors de la lecture\n");
        #endif
    }
    else
    {
      // On affiche un message d'erreur si on veut
      cerr<< "Impossible d'ouvrir le fichier \n"<<endl;
    }
}
