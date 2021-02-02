/*
ID: vittal.2
TASK: auto
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct dWord {
    string word;
    int index;
};

int sortcol (dWord w1, dWord w2){
    return w1.word < w2.word;
}

int binSearch(dWord dict[], int l, int r, string s){
    if(r >= l){
        int mid = (l+r)/2;
        if(dict[mid].word.compare(s) == 0)
            return mid;
        if(dict[mid].word.compare(s) > 0)
            return binSearch(dict, l, mid - 1, s);
        if(dict[mid].word.compare(s) < 0)
            return binSearch(dict, mid + 1, r, s);
    }
    
    return l;
}

int main() {
    ifstream fin ("auto.in");
    ofstream fout ("auto.out");

    int W, N;
    fin >> W >> N;
    
    dWord dict[W];
    for(int i = 0; i < W; i++){
        fin >> dict[i].word;
        dict[i].index = i;
    }
    
    int pTimes[N];
    string pWord[N];
    
    for(int i = 0; i < N; i++){
        fin >> pTimes[i] >> pWord[i];
    }
    
    sort(dict, dict+W, sortcol);

    int index;
    int count = 0;
    for(int i = 0; i < N; i++){
        index = binSearch(dict, 0, W-1, pWord[i]) + pTimes[i] - 1;
        if(index < W && dict[index].word.find(pWord[i]) == 0){
            fout << dict[index].index + 1 << endl;
        } else {
            fout << -1 << endl;
        }
        count = 0;
    }
    return 0;
}
