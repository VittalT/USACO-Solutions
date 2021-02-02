/*
ID: vittalt
TASK: berries
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
#include <cmath>

using namespace std;

int main()
{
    ofstream fout ("berries.out");
    ifstream fin ("berries.in");
    
    int N, K;
    fin >> N >> K;
    int b[N];
    
    for(int i = 0; i < N; i++)
        fin >> b[i];
    
    sort(b, b+N);
    int numMs = 0;
    int c[N];
    
    int maxSum = 0;
    int sum = 0;
    for(int m = 1; m <= b[N-1]; m++){
        numMs = 0;
        for(int i = 0; i < N; i++){
            numMs += b[i] / m;
            c[i] = b[i] % m;
        }
        sort(c, c+N);
        
        if(numMs >= K){
            maxSum = max(maxSum, m*K/2);
        } else if (numMs >= K/2){
            sum = m*(numMs - K/2);
            for(int i = 0; i < K - numMs && N-1-i >= 0; i++){
                sum += c[N-1-i];
            }
            maxSum = max(maxSum, sum);
        }
    }
    
    fout << maxSum;
    
    return 0;
}

