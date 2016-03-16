#include "../include/File.hpp"

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));
    Table mytable(0,0);
    vector<Piece*> mypile;
    
    if(argc>2)
    {
        string s1=string(argv[1]);
        string s2=string(argv[2]);
        string file_name="./txt/pieces_"+s1+"x"+s2+".txt";
        
        parseFile(&mytable,mypile,file_name);
        Chrono c=mytable.algoLocalSearch(mypile);
        
        cout << "Temps : "<<c.getTime() << endl;
        
        //mytable.showTable();
        mytable.getRes(argv[1],argv[2]);
    }
    
    return 0;
}
