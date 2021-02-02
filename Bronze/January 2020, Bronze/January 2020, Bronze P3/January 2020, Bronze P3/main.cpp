/*
ID: vittalt / vittal.2
TASK: race
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

long f(long maxV, long x){
    if(x >= maxV)
        return maxV * (maxV + 1) / 2;
    return maxV * maxV + (x - x * x)/2;
}

int main()
{
    ofstream fout ("race.out");
    ifstream fin ("race.in");
    
    int K, N;
    fin >> K >> N;
    
    int X[N];
    for(int i = 0; i < N; i++){
        fin >> X[i];
    }
    
    int x;
    int maxV = 0;
    long left;
    for(int i = 0; i < N; i++){
        x = X[i];
        
        while(f(maxV, x+1) < K){
            maxV++;
        }
        maxV--;
        
        if(maxV <= x){
            if(f(maxV+1, x+1) == K && maxV < x)
                maxV++;
            left = K - f(maxV, maxV);
            if(left == 0){
                fout << maxV << endl;
            } else if (left <= maxV){
                fout << maxV + 1 << endl;
            } else if (left<= 2 * maxV){
                fout << maxV + 2 << endl;
            } else {
                fout << maxV + 3 << endl;
            }
        } else {
            left = K - f(maxV, x+1);
            if(left <= x){
                fout << 2 * maxV - x << endl;
            } else if (left <= maxV + x){
                fout << 2 * maxV - x + 1 << endl;
            } else {
                fout << 2 * maxV - x + 2 << endl;
            }
        }
        
        maxV = 0;
    }
    
    
    return 0;
}

