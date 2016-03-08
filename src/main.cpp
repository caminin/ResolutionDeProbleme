#include "../include/File.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Table mytable(0,0);
    vector<Piece*> mypile;
    
    if(argc>2)
    {
        string s1=string(argv[1]);
        string s2=string(argv[2]);
        string file_name="./txt/pieces_0"+s1+"x0"+s2+".txt";
        
        parseFile(&mytable,mypile,file_name);
    }
    cout << mypile.size() << endl;
    Chrono c=mytable.algoCSP(mypile);
    
    cout << "Temps : "<<c.getTime() << endl;
    
    mytable.showTable();
    mytable.getRes();
    
    return 0;
}
