#include "../include/File.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Table *mytable;
    Pile *mypile;
#ifdef DEBUG

    string file_name=argc+argv[0];
    file_name="./txt/pieces_03x03.txt";
    {
#else
    if(argc>1)
    {
        string file_name=argv[1];
#endif
        parseFile(mytable,mypile,file_name);
    }
    return 0;
}