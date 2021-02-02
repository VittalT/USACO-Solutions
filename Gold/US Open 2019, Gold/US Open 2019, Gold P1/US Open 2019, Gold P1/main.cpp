/*
ID: vittal.2
TASK: snakes
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
#include <unordered_map>
#include <deque>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <unordered_set>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef deque<int> qi;

int N, K;
int snakes[405], dp[405][405];

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    
    cin >> N >> K;
    int sum = 0;
    FOR(i, 1, N+1) {
        cin >> snakes[i];
        sum += snakes[i];
    }
    
    int max_val = 0;
    FOR (i, 1, N+1) {
        max_val = max(max_val, snakes[i]);
        dp[i][0] = i * max_val;
    }
    
    FOR(i, 1, N+1) FOR(j, 1, K+1) {
        max_val = 0;
        dp[i][j] = INT_MAX;
        R0F(k, i) {
            max_val = max(max_val, snakes[k+1]);
            dp[i][j] = min(dp[i][j], dp[k][j-1] + (i-k) * max_val);
        }
    }
    
    cout << dp[N][K] - sum << endl;
    
    return 0;
}

// Too much memory
/*
int N, K;
int snakes[405];
set<int> poss_sizes;
unordered_map<int, int> dp[405][405];
int min_dp[405][405];

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    
    cin >> N >> K;
    FOR(i, 1, N+1) {
        cin >> snakes[i];
        poss_sizes.insert(snakes[i]);
    }
    
    F0R(i, N+1) F0R (j, K+1) for (int net_size : poss_sizes) {
        dp[i][j][net_size] = 0x3f3f3f3f;
    }
    memset(min_dp, 0x3f, sizeof(min_dp));
    
    F0R (j, K+1) {
        for (int poss_size : poss_sizes) {
            dp[0][j][poss_size] = 0;
        }
        min_dp[0][j] = 0;
    }
    
    int new_waste;
    FOR(i, 1, N+1) F0R (j, K+1) {
        for (int net_size : poss_sizes) {
            if ((new_waste = net_size - snakes[i]) >= 0) {
                int& cur = dp[i][j][net_size];
                if (j > 0) cur = min(cur, min_dp[i-1][j-1] + new_waste);

                auto state=dp[i-1][j].find(net_size);
                if (state != dp[i-1][j].end()) {
                    cur = min(cur, state->s + new_waste);
                }
                min_dp[i][j] = min(min_dp[i][j], cur);
            }
        }
    }
    
    cout << min_dp[N][K] << endl;
    
    return 0;
}
*/
