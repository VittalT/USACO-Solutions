/*
NAME: Vittal Thirumalai
TASK: deleg
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
typedef deque<int> qi;

const int MAX = 1e5 + 5;
int N;
vi adj[MAX], adjSz[MAX];
bool poss[MAX];
int sz[MAX];

/*
int dfs(int n, int p, int num) {
    map<int, int> freq;
    if (adj[n].size() == 1 && n != 1) {
        cout << "Leaf. ";
    }
    int needed = 0, count = 0;
    for (int t : adj[n]) if (t != p) {
        count++;
        needed = dfs(t, n, num);
        //printf("On %d. From %d need %d.\n", n, t, num_needed);
        if (needed == -1) return -1;
        freq[(needed + num-1) % num]++;
    }
    if (count == 1) return (needed + num-1) % num;

    needed = 0;
    int a, b;
    for (pi x : freq) if (x.f) {
        if (2 * x.f == num) {
            if (x.s % 2) {
                if (needed != 0 && needed != x.f) return -1;
                needed = x.f;
            }
        }
        else {
            a = x.s; b = freq[num - x.f];
            //printf("On %d. %d:%d and %d:%d\n", n, x.f, a, num-x.f, b);
            if (a != b) {
                int new_needed;
                if (a == b + 1) new_needed = x.f;
                else if (a + 1 == b) new_needed = num - x.f;
                else return -1;
                if (needed && needed != new_needed) return -1;
                needed = new_needed;
            }
        }
    }
    //printf("Num %d: %d parent %d; needed %d\n", num, n, p, needed);
    return needed;
}
*/

void dfs(int n, int p) {
    sz[n] = 1;
    for (int t : adj[n]) if (t != p) {
        dfs(t, n);
        sz[n] += sz[t];
        adjSz[n].pb(sz[t]);
    }
    if (sz[n] != N) adjSz[n].pb(N-sz[n]);
}

int freq[MAX];
bool ok(int K) {
    if ((N-1) % K != 0) return false;
    memset(freq, 0, sizeof(freq));
    FOR(n, 1, N+1) {
        int cnt = 0;
        for (int nbSz : adjSz[n]) {
            int needed = nbSz % K; if (needed == 0) continue;
            if (freq[K-needed]) {freq[K-needed]--; cnt--;}
            else {freq[needed]++; cnt++;}
        }
        if (cnt) return false;
    }
    return true;
}

//vi allDivisors(int n) {
//    vi allDiv;
//    FOR(i, 1, n+1) if (n % i == 0) allDiv.pb(i);
//    return allDiv;
//}

int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    cin >> N;
    int a, b;
    F0R(i, N-1) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(1,0);
    
//    vi allDiv = allDivisors(N-1); int div;
//    R0F(i, (int)allDiv.size()) {
//        div = allDiv[i];
//        if (!poss[div]) {
//            poss[div] = ok(div);
//            if (poss[div]) for (int divdiv : allDivisors(div)) poss[divdiv] = true;
//        }
//    }
    
    FOR(i, 1, N) cout << ok(i);
    cout << endl;
    
    return 0;
}

