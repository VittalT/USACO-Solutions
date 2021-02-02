/*
ID: vittalt
TASK: leftout
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <queue>

using namespace std;

int N;
string cows[1000];

void changeRow(int row){
    for(int i = 0; i < N; i++){
        if(cows[row][i] == 'R')
            cows[row][i] = 'L';
        else if(cows[row][i] == 'L')
            cows[row][i] = 'R';
    }
}

void changeCol(int col){
    for(int i = 0; i < N; i++){
        if(cows[i][col] == 'R')
            cows[i][col] = 'L';
        else if(cows[i][col] == 'L')
            cows[i][col] = 'R';
    }
}

int main()
{
    ofstream fout ("leftout.out");
    ifstream fin ("leftout.in");
    
    fin >> N;
    for(int i = 0; i < N; i++)
        fin >> cows[i];
    
    if(N == 2) {
        fout << 1 << " " << 1;
        return 0;
    }
    
    for(int i = 0; i < N; i++){
        if(cows[0][i] == 'L')
            changeCol(i);
    }
    
    vector< pair<int,int> > posBad;
    
    for(int i = 1; i < N; i++){
        
        if(cows[i][0] == 'L' && cows[i][1] == 'L' && cows[i][2] == 'L')
            changeRow(i);
        for(int j = 0; j < 3; j++)
            if(cows[i][j] == 'R' && cows[i][(j+1)%3] == 'L' && cows[i][(j+2)%3] == 'L')
                changeRow(i);
        
        for(int j = 0; j < N; j++){
            if(cows[i][j] != 'R'){
                posBad.push_back(make_pair(i, j));
            }
        }
    }
    
    if(posBad.size() == 0){
        fout << -1;
    }
    else if(posBad.size() == 1){
        fout << posBad[0].first + 1 << " " << posBad[0].second + 1;
    } else {
        int badCol = posBad[0].second;
        for(auto p : posBad){
            if(p.second != badCol){
                fout << -1;
                return 0;
            }
        }
        if(posBad.size() != N-1) {
            fout << -1;
            return 0;
        }
        fout << 1 << " " << badCol + 1;
    }
    
    return 0;
}
