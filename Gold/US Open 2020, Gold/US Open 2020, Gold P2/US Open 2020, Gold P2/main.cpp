/*
NAME: Vittal Thirumalai
TASK: fcolor
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
#define pb push_back
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef queue<int> qi;
typedef long long LL;

const int MAX = 2e5 + 5;
int N, M;
vi adj[MAX];
int par[MAX], sz[MAX], color[MAX];
//int group[MAX], adjColor[MAX];
qi q;

int get(int x){
    return x == par[x] ? x : par[x] = get(par[x]);
}

void unite (int a, int b) {
    a = get(a); b = get(b); if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a; sz[a] += sz[b];
    adj[a].insert(adj[a].end(), adj[b].begin(), adj[b].end());
    adj[b].clear();
    if (adj[a].size() > 1) q.push(a);
}

void merge(int a, int b) {
    a = get(a); b = get(b); if (a == b) return;
    if (adj[a].size() < adj[b].size()) swap(a, b);
    par[b] = a;
    adj[a].insert(adj[a].end(), adj[b].begin(), adj[b].end());
    adj[b].clear();
    if (adj[a].size() > 1) q.push(a);
}

int main() {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    
    cin >> N >> M;
    F0R(i, M) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
    }
    
    FOR(i, 1, N+1) {
        par[i] = i;
        if (adj[i].size() > 1) q.push(i);
    }
    
    while(!q.empty()) {
        int x = q.front();
        if (adj[x].size() <= 1) {q.pop(); continue;}
        int a = adj[x].back(); adj[x].pop_back();
        int b = adj[x].back();
        unite(a, b);
    }
    
    int g = 1;
    FOR(i, 1, N+1) {
        int rep = get(i);
        if (!color[rep]) color[rep] = g++;
        cout << color[rep] << endl;
    }
    
//    int g = 1;
//
//    FOR(i, 1, N) {
//        for (int rn : radj[i]){
//            if (color[rn] && adjColor[color[rn]]) color[i] = adjColor[color[rn]];
//        }
//        if (!color[i]) {
//            color[i] = g++;
//            for (int rn : radj[i]){
//                if (color[rn]) adjColor[color[rn]] = color[i];
//            }
//        }
//
//        for (int n : adj[i]) {
//            group[n] = color[i];
//            if (adjColor[color[i]]) color[n] = adjColor[color[i]];
//        }
//    }
    
    return 0;
}

