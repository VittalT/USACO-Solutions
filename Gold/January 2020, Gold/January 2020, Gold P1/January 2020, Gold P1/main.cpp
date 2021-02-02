/*
ID: vittal.2
TASK: time
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

int N, M, C;
int m[1005], dist[1005][1005];
vector<pi> adj[1005];

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    
    cin >> N >> M >> C;
    FOR(i, 1, N+1) cin >> m[i];
    
    int a, b;
    F0R(i, M) {
        cin >> a >> b;
        adj[a].push_back({b, -m[b]});
    }
    
    memset(dist, 0x3f, sizeof(dist));
    dist[1][0] = 0;
    
    int max_moonies = 0;
    FOR(t, 1, 1000 / C + 1) {
        FOR(u, 1, N+1) for (pi v : adj[u]) {
            if (dist[v.f][t] > dist[u][t-1] + v.s) {
                dist[v.f][t] = dist[u][t-1] + v.s;
            }
        }
        max_moonies = max(max_moonies, -dist[1][t] - C * t * t);
    }
    
    cout << max_moonies << endl;
    return 0;
}
