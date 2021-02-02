/*
NAME: Vittal Thirumalai
TASK: timeline
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */

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

const int MAX = 1e5 + 5;
int N, M, C;
stack<int> st;
vector<pi> adj[MAX];
int S[MAX];
bool visited[MAX];

void dfs(int n) {
    visited[n] = true;
    for (pi t : adj[n]) if (!visited[t.f]) dfs(t.f);
    st.push(n);
}

int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
    
    cin >> N >> M >> C;
    FOR(i, 1, N+1) cin >> S[i];
    int a, b, x;
    F0R(i, C) {
        cin >> a >> b >> x;
        adj[a].push_back({b,x});
    }
    
    FOR(i, 1, N+1) if (!visited[i]) dfs(i);
    
    while(st.size()) {
        int cur = st.top(); st.pop();
        for (pi nb : adj[cur]) {
            S[nb.f] = max(S[nb.f], S[cur] + nb.s);
        }
    }
    
    FOR(i, 1, N+1) cout << S[i] << endl;    
    return 0;
}
