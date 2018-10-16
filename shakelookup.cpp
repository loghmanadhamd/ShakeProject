#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include "index.h"
#include "Stem/english_stem.h"



using namespace std;

//Text stream path for the text file
const string path = "/home/class/SoftDev/Shakespeare/";
const string filename = path + "Shakespeare.txt";
vector<string> getWords(string line);
string removeSpecials(string str);

int main() {
    stemming::english_stem<char, std::char_traits<char> > StemEnglish;
    ifstream shakefile;
//opening shakespeare file
    shakefile.open(filename);
    if (!shakefile.is_open()) {
        cout << "File (" << filename << ") not found. Goodbye." << endl;
    } else {
        cout << "File (" << filename << ") open!";
        cout << endl;

    }
    bookIndex index;
    int p = shakefile.tellg();
    cout << p << endl;

//Getting lines from shakespeare file
    while (!shakefile.eof()) {
        string line;
        getline(shakefile, line);
        vector<string> word = getWords(line);

        for (int i = 0; i < word.size(); i++) {
//Stemming words in the shakespeare file
            transform(word[i].begin(), word[i].end(), word[i].begin(), ::toupper);
            string saveWord = word[i];
            /* Reduce to Stem */
            StemEnglish(word[i]);

 //Add stemmed words to the index
            index.add(word[i], p);
        }
        p = shakefile.tellg();

    }

    string shake, buffer;
  //Search word request 
    cout << endl << "Enter a word to search: ";
    cin>>shake;

    /* Convert word to upper case-- stemming searched word*/
    transform(shake.begin(), shake.end(), shake.begin(), ::toupper);
    string saveWord = shake;
    /* Reduce to Stem */
    StemEnglish(shake);
    cout << "The stemmed version of \"" << saveWord << "\" is \"" << shake << "\"" << endl;

    vector<int> list = index.lookup(shake);
    //add normalize case

    cout << "Number of times the word " << shake << " appeared: " << list.size() << endl;
    string input = "";


    string pos;
    //Closing and reopening file
    shakefile.close();
    shakefile.open(filename);
    
    //Searching word and reading out lines containing the desired word 
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << "---";
        shakefile.seekg(list[i]);
        getline(shakefile, pos);
        cout << pos << endl;


    }

    cout << "END OF PROGRAM!" << endl;

    return 0;
}

//finding words in each line of the file
vector<string> getWords(string line) {
    istringstream iss(line);
    vector<string> words;
    string s;
    do {
        iss >> s;
        if (s.length() > 0 && s != " ") {
            words.push_back(s);

        }
        s = "";
    } while (iss);
    return words;

}
//removing special characters from the textfile 
string removeSpecials(string str) {
    int i = 0, len = str.length();
    while (i < len) {
        char c = str[i];
        if (((c >= '0')&&(c <= '9')) || ((c >= 'A')&&(c <= 'Z')) || ((c >= 'a')&&(c <= 'z')) || c == '\'' || c == ' ') {
            if ((c >= 'A')&&(c <= 'Z')) str[i] += 32; //Assuming dictionary contains small letters only.
            ++i;
        } else {
            str.erase(i, 1);
            --len;
        }
    }
    return str;
}

//test for git HW
