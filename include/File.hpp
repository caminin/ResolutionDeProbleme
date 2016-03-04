#ifndef __MYFILE
#define __MYFILE

#include "Table.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<int> &split(const string &s, char delim, vector<int> &elems) ;
vector<int> split(const string &s, char delim);
void parseFile(Table *mytable, vector<Piece*> &mypile,string file_name);



#endif
