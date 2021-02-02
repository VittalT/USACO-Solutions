/*
ID: vittal.2
TASK: convention
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

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

int N, M, C;
int times[100000];

int min_buses(int max_time, int start) {
    if (start >= N) return 0;
    
    int index = start;
    while (index < N && times[index] <= times[start] + max_time) ++index;
    index = min(index, start + C);
    return 1 + min_buses(max_time, index);
}

bool poss(int max_time) {
    return min_buses(max_time, 0) <= M;
}

int bin_search(int left, int right) {
    int mid = (left + right) / 2;
    if (!poss(mid)) return bin_search(mid+1, right);
    if (poss(mid-1)) return bin_search(left, mid-1);
    return mid;
}

int main()
{
    ofstream fout ("convention.out");
    ifstream fin ("convention.in");

    fin >> N >> M >> C;
    F0R (i, N) fin >> times[i];
    
    sort(times, times+N);
    fout << bin_search(0, 1000000000) << endl;
    return 0;
}
