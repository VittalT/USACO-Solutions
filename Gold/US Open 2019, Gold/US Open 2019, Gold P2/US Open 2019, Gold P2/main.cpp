/*
ID: vittal.2
TASK: walk
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

long long N, K;
long long w[7505];
bool visited[7505];

int main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    
    cin >> N >> K;
    
    FOR(i, 1, N+1) w[i] = 2019201997;
    w[1] = 0;
    F0R(c, N) {
        int min_i = -1; long long min_val = 2019201998;
        FOR(i, 1, N+1) if (!visited[i]) {
            if (w[i] < min_val) {
                min_val = w[i];
                min_i = i;
            }
        }
        visited[min_i] = true;
        FOR(j, 1, N+1) if (!visited[j]) {
            w[j] = min(w[j], (2019201913LL * min(min_i,j) + 2019201949LL * max(min_i,j)) % 2019201997LL);
        }
    }
    
    sort(w+1, w+N+1);
    cout << w[N-K+2] << endl;
    
    
    // One-line math solution! LOL
    // cout << 2019201997 - (84 * (K-1) + 48 * N) << endl;
    return 0;
}
