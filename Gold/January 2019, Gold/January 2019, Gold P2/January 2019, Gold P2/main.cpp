/*
ID: vittal.2
TASK: sleepy
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <queue>
#include <tuple>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;

/*
int main() {
    ofstream fout ("sleepy.out");
    ifstream fin ("sleepy.in");
    
    int N;
    fin >> N;
    deque<int> cows(N);
    
    for(int i = 0; i < N; i++){
        fin >> cows[i];
    }
    
    int critIndex = N - 1;
    
    while(critIndex > 0 && cows[critIndex-1] < cows[critIndex]){
        critIndex--;
    }
    
    fout << critIndex << endl;
    
    for(int i = 0; i < critIndex; i++){
        int index = distance(cows.begin(), lower_bound(cows.begin()+critIndex-i, cows.end(), cows.front()));
        cows.insert(cows.begin()+index, cows.front());
        cows.pop_front();
        fout << index - 1 << ((i == critIndex - 1 ) ? "" : " ");
    }
    
    fout << endl;
    
    return 0;
}
*/

const int MAX = 100005;
int N;
int cows[MAX];
int fk[MAX];

void inc(int i) {
    for(++i; i <= N; i += i&-i) {
        fk[i]++;
    }
}

int getSum(int i) {
    int sum = 0;
    for(++i; i > 0; i -= i&-i) {
        sum += fk[i];
    }
    return sum;
}

int main() {
    ofstream fout ("sleepy.out");
    ifstream fin ("sleepy.in");
    
    fin >> N;
    F0R(i, N) fin >> cows[i];
    
    int critIndex = N - 1;
    
    while(critIndex > 0 && cows[critIndex-1] < cows[critIndex]){
        critIndex--;
    }
    
    fout << critIndex << endl;
    
    FOR(i, critIndex, N) inc(cows[i]);
    
    F0R(i, critIndex) {
        fout << getSum(cows[i]) + critIndex - 1 - i;
        if (i != critIndex - 1) fout << " ";
        inc(cows[i]);
    }
    
    fout << endl;
    
    return 0;
}
