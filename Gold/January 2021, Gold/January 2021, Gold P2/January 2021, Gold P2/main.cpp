#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <climits>
#include <fstream>
#include <string>
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
const int MAXN = 5e4 + 5;
const int MAXK = 55;
int breed[MAXN], dist[MAXN];
vector<int> adj[MAXN];
int b_adj[MAXK][MAXK];

int dijkstra(int src, int end) {
    priority_queue<pi> pq;
    memset(dist, 0x3f, sizeof(dist));
    dist[src] = 0;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (weight != dist[u]) continue;
        if (u == end) return dist[u];

        for (int v : adj[u]) {
            //cout << u << "->" << v << endl;
            int new_weight = weight + abs(u - v);
            if (dist[v] < dist[u] + new_weight) {
                dist[v] = dist[u] + new_weight;
                pq.push({dist[v], v});
            }
        }
    }
    return -1;
}

int main() {
    
    cin >> N >> K;
    FOR(i, 1, N+1) {
        cin >> breed[i];
    }
    
    string str;
    FOR(i, 1, K+1) {
        cin >> str;
        FOR(j, 1, K+1) {
            b_adj[i][j] = str.at(j-1);
        }
    }   
    
    FOR(i, 1, N+1) FOR(j, 1, N+1) {
        if (b_adj[breed[i]][breed[j]]) {
            //cout << i << " " << j << endl;
            adj[i].push_back(j);
        }
    }
    
    int ans = dijkstra(1, N);
    
    cout << ans << endl;
    return 0;
}
