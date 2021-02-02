/*
ID: vittal.2
TASK: cowmbat
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

int main()
{
    ofstream fout ("cowmbat.out");
    ifstream fin ("cowmbat.in");
    
    int N, M, K;
    fin >> N >> M >> K;
    string s;
    fin >> s;
    
    int combo [N];
    F0R (i, N)
        combo[i] = (int)s[i] - 97;
    
    int dist[M][M];
    F0R (i, M)
        F0R (j, M)
            fin >> dist[i][j];
    
    // Floyd Warshall
    F0R (k, M)
        F0R (i, M)
            F0R (j, M)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    
    // Dynamic Programming
    int dp[N+1][M], min_dp[N+1];
    int cost[M];
    memset(cost, 0, sizeof(cost));
    memset(min_dp, 0x3f, sizeof(min_dp));
    
    F0R (c, M)
        F0R (i, K)
            cost[c] += dist[combo[i]][c];
    
    F0R (c, M) {
        dp[K][c] = cost[c];
        min_dp[K] = min(min_dp[K], dp[K][c]);
    }
    
    FOR (i, K+1, N+1) {
        F0R (c, M) {
            dp[i][c] = dp[i-1][c] + dist[combo[i-1]][c];
            cost[c] = cost[c] - dist[combo[i-K-1]][c] + dist[combo[i-1]][c];
            if (i >= 2*K) {
                dp[i][c] = min(dp[i][c], min_dp[i-K] + cost[c]);
            }
            min_dp[i] = min(min_dp[i], dp[i][c]);
        }
    }
    
    fout << min_dp[N] << endl;
    return 0;
}
