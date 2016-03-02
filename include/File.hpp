#ifndef __MYFILE
#define __MYFILE

#include "Table.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) ;
vector<string> split(const string &s, char delim);
void parseFile(string file_name);



#endif
