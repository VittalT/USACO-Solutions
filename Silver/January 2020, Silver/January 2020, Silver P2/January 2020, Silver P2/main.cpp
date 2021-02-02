/*
ID: vittalt
TASK: loan
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
typedef long long LL;

LL N, K, M;

bool Milk(LL x){
    LL sum = 0;
    LL count = 0;
    LL Y;
    LL num;
    while (count < K){
        Y = (N-sum)/x;
        if(Y <= M){
            sum += M * (K - count);
            count = K;
        } else {
            num = min((N-sum)/Y - x + 1, K - count);
            count += num;
            sum += Y * num;
        }
    }
    
    return sum >= N;
}

LL binarySearch(LL l, LL r)
{
    LL mid = (l+r) / 2;
    if (!Milk(mid)) return binarySearch(l, mid-1);
    if (Milk(mid+1)) return binarySearch(mid+1, r);
    return mid;
}

int main()
{
    ofstream fout ("loan.out");
    ifstream fin ("loan.in");
    
    fin >> N >> K >> M;
    fout << binarySearch(1, N/M);
    
    return 0;
}

