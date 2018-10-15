#include "index.h"

bookIndex::bookIndex(){
}
void bookIndex::add(string word, int p){
	index[word].push_back(p);
}
vector<int> bookIndex::lookup(string word){
	return index[word];
}