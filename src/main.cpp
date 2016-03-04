#include "../include/File.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Table mytable(0,0);
    vector<Piece*> mypile;
#ifdef DEBUG

    string file_name=argc+argv[0];
    file_name="./txt/pieces_05x05.txt";
    {
#else
    if(argc>1)
    {
        string file_name=argv[1];
#endif
        parseFile(&mytable,mypile,file_name);
    }
    cout << mypile.size() << endl;
    Chrono c=mytable.algoCSP(mypile);
    
    cout << "Temps : "<<c.getTime() << endl;
    
    mytable.showTable();
    
    return 0;
}
