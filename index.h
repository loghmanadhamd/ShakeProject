#ifndef INDEX_H
#define INDEX_H
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

class bookIndex {

public:
bookIndex();
void add(string word, int p);
vector<int> lookup(string word);


private:
map<string,vector<int>>index;


};

#endif /* INDEX_H */