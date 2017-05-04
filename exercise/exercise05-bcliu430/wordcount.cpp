#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool mycompare(const pair <string, size_t>  &x,
               const pair <string, size_t>  &y) {

    return x.second > y.second;
}

void wordcount(string inf);

int main(){
    ifstream filein("prose.txt");

    if (!filein.is_open()){
        cerr << "Error when opening the file, exit!\n";
        return -1;
    }
    else
        wordcount("prose.txt");

    filein.close();

    return 0;
}


void wordcount(string inf){

    typedef unordered_map <string, size_t> DictType;
    DictType dict;

    ifstream infi(inf);

    string word;
    while (!infi.eof()){
        infi >> word;
        dict[word] +=1;
    }

    cout << "total number of words is "<< dict.size() << endl;

    typedef vector <pair <string, size_t> > VecType;
    VecType words;

    copy(dict.begin(), dict.end(), back_inserter(words));

    sort(words.begin(), words.end(), mycompare);

    for (size_t i = 0; i <10 && i < words.size(); ++i){
        cout << words[i].first << ": " << words[i].second << endl;
    }

    return ;
}
