/*
ID: vittalt
TASK: triangles
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
typedef long long LL;

const int MAX = 2505;
int N, sum, c[MAX], numParity[2];
vi adj[MAX];
bool depthParity[MAX];

void dfs(int n, int p) {
    depthParity[n] = !depthParity[p];
    sum = (sum + (depthParity[n] ? 1 : -1) * c[n] + 12) % 12;
    numParity[depthParity[n]]++;
    for (int t : adj[n]) if (t != p) dfs(t, n);
}

int main()
{
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);
    
    cin >> N;
    int a, b;
    FOR(i, 1, N+1) cin >> c[i];
    F0R(i, N-1) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, 0);
    int ans;
    if (sum == 0) ans = N;
    else if (sum == 1) ans = numParity[1];
    else if (sum == 11) ans = numParity[0];
    else ans = 0;
    
    cout << ans << endl;
    return 0;
}
