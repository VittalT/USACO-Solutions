/*
ID: vittal.2
TASK: shuffle
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> reverseShuffle(vector<int> cows, vector<int> shuffle){
    vector<int> newCows(cows.size());
    
    for(int i = 0; i < cows.size(); i++) {
        newCows.at(i) = cows.at(shuffle.at(i)-1);
    }
    return newCows;
}

int main() {
    ofstream fout ("shuffle.out");
    ifstream fin ("shuffle.in");
    
    int N;
    fin >> N;
    
    vector<int> shuffle(N);
    for(int i = 0; i < N; i++){
        fin >> shuffle.at(i);
    }
    
    vector<int> cows(N);
    for(int i = 0; i < N; i++){
        fin >> cows.at(i);
    }
    
    for(int i = 0; i < 3; i++){
        cows = reverseShuffle(cows, shuffle);
    }
    
    for(int i = 0; i < N-1; i++){
        fout << cows.at(i) << endl;
    }
    fout << cows.at(N-1);
    
    return 0;
}
