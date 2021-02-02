#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)

int N, count;
vector<int> adj[100005];

int dfs(int n, int p) {
    int num = 0;
    for (int t : adj[n]) if (t != p) {
        num += dfs(t, n) + 1;
    }
    return num + ceil(log2(adj[n].size()));
}

int main() {
    cin >> N;
    int a, b;
    F0R(i, N-1) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    adj[1].push_back(0);
    
    cout << dfs(1,0) << endl;
    return 0;
}
