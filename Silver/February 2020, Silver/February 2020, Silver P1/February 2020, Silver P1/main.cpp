/*
ID: vittalt
TASK: swap
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

int N, M, K;
int cows[100002];
bool visited[100002];
vector<int> swaps[100002];
int L[100];
int R[100];

int main()
{
    ofstream fout ("swap.out");
    ifstream fin ("swap.in");
    
    fin >> N >> M >> K;
    
    for(int i = 0; i < M; i++){
        fin >> L[i] >> R[i];
    }
    
    for(int i = 1; i <= N; i++){
        cows[i] = i;
    }
    
    int l, r, temp;
    for(int i = 0; i < M; i++){
        l = L[i];
        r = R[i];
        while(l < r){
            temp = cows[l];
            cows[l] = cows[r];
            cows[r] = temp;
            l++;
            r--;
        }
    }
    
    int index = 0;
    int cur;
    for(int i = 1; i <= N; i++){
        if(!visited[cows[i]]){
            cur = cows[i];
            do {
                swaps[index].push_back(cur);
                visited[cur] = true;
                cur = cows[cur];
            } while(cur != cows[i]);
            
            index++;
        }
    }
    
    
    for(int i = 0; i < index; i++){
        for(int j = 0; j < swaps[i].size(); j++)
            cows[swaps[i][j]] = swaps[i][(j+K) % swaps[i].size()];
    }
    
    for(int i = 1; i <= N; i++)
        fout << cows[i] << endl;
}
