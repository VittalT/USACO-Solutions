/*
ID: vittal.2
TASK: cowland
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
typedef vector<int> vi;
typedef deque<int> qi;


int N, logN, Q;
const int MAX = 100005;
const int LOGMAX = 20;
int e[MAX], depth[MAX], ST[MAX][LOGMAX];
int treesz[MAX], topChain[MAX], segtreeID[MAX];
vi adj[MAX];

int segtree[4 * MAX];

void segtreeupd(int idx, int l, int r, int i, int val) {
    if (l == r) {
        segtree[idx] = val;
        return;
    }
    int m = (l+r) / 2;
    if (i <= m) segtreeupd(idx*2, l, m, i, val);
    else segtreeupd(idx*2+1, m+1, r, i, val);
    segtree[idx] = segtree[idx*2] ^ segtree[idx*2+1];
}

void segtreeupd(int i, int val) {
    segtreeupd(1, 0, N, i, val);
}

int segtreeqry(int idx, int l, int r, int left, int right) {
    if (left <= l && r <= right) return segtree[idx];
    int ret = 0;
    int m = (l+r) / 2;
    if (m >= left) ret ^= segtreeqry(idx*2, l, m, left, right);
    if (m+1 <= right) ret ^= segtreeqry(idx*2+1, m+1, r, left, right);
    return ret;
}

int segtreeqry(int l, int r) {
    return segtreeqry(1, 0, N, l, r);
}

void dfs(int n, int p) {
    ST[n][0] = p; depth[n] = depth[p] + 1;
    treesz[n]++;
    for (int t : adj[n]) if (t != p) {
        dfs(t, n);
        treesz[n] += treesz[t];
    }
}

void initST() {
    FOR(j, 1, logN) FOR(i, 1, N+1) {
        ST[i][j] = ST[ST[i][j-1]][j-1];
    }
}

void dfsSegtree(int n, int nTopChain, int p, int& ID) {
    segtreeID[n] = ID++;
    segtreeupd(segtreeID[n], e[n]);
    topChain[n] = nTopChain;
    int maxSize = -1, maxChild = -1;
    for (int t : adj[n]) if (t != p) {
        if (treesz[t] > maxSize) {
            maxSize = treesz[t];
            maxChild = t;
        }
    }
    if (maxChild == -1) return;
    
    dfsSegtree(maxChild, nTopChain, n, ID);
    for (int t : adj[n]) if (t != p && t != maxChild) {
        dfsSegtree(t, t, n, ID);
    }
}

void initHLD() {
    dfs(1,0);
    initST();
    int startID = 0;
    dfsSegtree(1, 1, 0, startID);
}

int qry(int n, int p) {
    if (n == p) return 0;
    if (topChain[n] == n) {
        // light
        return e[n] ^ qry(ST[n][0], p);
    } else if (depth[topChain[n]] > depth[p]) {
        // heavy, not reached parent
        int topChild = topChain[n];
        return segtreeqry(segtreeID[topChild], segtreeID[n]) ^ qry(ST[topChild][0], p);
    } else {
        // heavy, reached parent
        return segtreeqry(segtreeID[p]+1, segtreeID[n]);
    }
}

// Alternate iterative version

//int qry(int n, int p) {
//    int ret = 0;
//    while (n != p) {
//        if (topChain[n] == n) {
//            // light
//            ret ^= e[n];
//            n = ST[n][0];
//        } else if (depth[topChain[n]] > depth[p]) {
//            // heavy, not reached parent
//            int topChild = topChain[n];
//            ret ^= segtreeqry(segtreeID[topChild], segtreeID[n]);
//            n = ST[topChild][0];
//        } else {
//            // heavy, reached parent
//            ret ^= segtreeqry(segtreeID[p]+1, segtreeID[n]);
//            break;
//        }
//    }
//    return ret;
//}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    R0F(j, logN) if (1 << j <= diff) {
        a = ST[a][j];
        diff -= 1 << j;
    }
    R0F(j, logN) if (ST[a][j] != ST[b][j]) {
        a = ST[a][j];
        b = ST[b][j];
    }
    if (a != b) a = ST[a][0];
    return a;
}

int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    
    cin >> N >> Q;
    logN = ceil(log2(N));
    FOR(i, 1, N+1) cin >> e[i];
    int a, b, c;
    F0R(i, N-1) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    initHLD();
    F0R(i, Q) {
        cin >> a >> b >> c;
        if (a == 1) {
            e[b] = c;
            segtreeupd(segtreeID[b], e[b]);
        } else {
            int l = lca(b, c);
            cout << (qry(b, l) ^ qry(c, l) ^ e[l]) << endl;
        }
    }
    
    return 0;
}

 
 
/*
int N, logN, Q;
const int MAX = 100005;
const int LOGMAX = 20;
int e[MAX], XOR[MAX], parent[MAX], depth[MAX], ST[MAX][LOGMAX];
vi adj[MAX];

void dfs(int n, int p) {
    parent[n] = p; depth[n] = depth[p] + 1;
    XOR[n] = XOR[p] ^ e[n];
    for (int t : adj[n]) if (t != p) dfs(t, n);
}

void updateST() {
    FOR(i, 1, N+1) ST[i][0] = parent[i];
    FOR(j, 1, logN) FOR(i, 1, N+1) {
        ST[i][j] = ST[ST[i][j-1]][j-1];
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    R0F(j, logN) if (1 << j <= diff) {
        a = ST[a][j];
        diff -= 1 << j;
    }
    R0F(j, logN) if (ST[a][j] != ST[b][j]) {
        a = ST[a][j];
        b = ST[b][j];
    }
    if (a != b) a = ST[a][0];
    return a;
}

int main() {
    ofstream fout ("cowland.out");
    ifstream fin ("cowland.in");
    
    fin >> N >> Q;
    logN = ceil(log2(N));
    FOR(i, 1, N+1) fin >> e[i];
    int a, b, c;
    F0R(i, N-1) {
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    updateST();
    F0R(i, Q) {
        fin >> a >> b >> c;
        if (a == 1) {
            e[b] = c;
            dfs(b,parent[b]);
        } else {
            int l = lca(b, c);
            fout << (XOR[b] ^ XOR[c] ^ e[l]) << endl;
        }
    }
    
    return 0;
}
*/
