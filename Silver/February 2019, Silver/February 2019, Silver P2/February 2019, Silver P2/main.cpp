/*
ID: vittal.2
TASK: paintbarn
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
#include <stack>
#include <tuple>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;
typedef deque<int> qi;

int N, K;
int dp[1001][1001];

int main() {
    
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    
    cin >> N >> K;
    int a, b, c, d;
    F0R(i, N) {
        cin >> a >> b >> c >> d;
        ++a; ++b; ++c; ++d;
        dp[a][b]++;
        dp[a][d]--;
        dp[c][b]--;
        dp[c][d]++;
    }
    
    int ret = 0;
    FOR(i, 1, 1001) FOR (j, 1, 1001) {
        dp[i][j] += (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
        if (dp[i][j] == K) ret++; // point (i+1, j+1)
    }
    
    cout << ret << endl;
}
/*
int main() {
    ofstream fout ("paintbarn.out");
    ifstream fin ("paintbarn.in");
    int N, K;
    fin >> N >> K;
    
    for(int i = 0; i < N; i++) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        
        for(int i = a; i < c; i++) {
            dp[i][b]++;
            dp[i][d]--;
        }
    }
    
    int ret = 0;
    
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if(dp[i][j] == K) ret++;
            dp[i][j+1] += dp[i][j];
        }
    }
    
  fout << ret << endl;
}
*/
