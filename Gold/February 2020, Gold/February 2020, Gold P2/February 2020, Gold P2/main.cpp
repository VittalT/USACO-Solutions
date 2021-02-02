/*
NAME: Vittal Thirumalai
TASK: help
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <numeric>
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
typedef long long LL;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef deque<int> qi;

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
int N;
bool type[2 * MAX];
int prf[2 * MAX];

bool compEnd(pi s1, pi s2) {
    return s1.s < s2.s;
}

LL powmod(int base, int exp) {
    if (exp == 0) return 1LL;
    LL ans = powmod(base, exp/2);
    ans = ans*ans % MOD;
    if (exp % 2) ans = (ans * base) % MOD;
    return ans;
}

//int main() {
//    freopen("help.in", "r", stdin);
//    freopen("help.out", "w", stdout);
//
//    cin >> N;
//    int l, r;
//    F0R(i, N) {
//        cin >> l >> r;
//        type[l] = 1;
//        prf[l] += 1;
//        prf[r+1] += -1;
//    }
//
//    LL sum = 0; int active = 0;
//    FOR(i, 1, 2*N) {
//        active += prf[i];
//        if (type[i]) sum = (sum + powmod(2,N-active)) % MOD;
//    }
//
//    cout << sum << endl;
//    return 0;
//}

vector<long> getMaxArea(int w, int h, vector<bool> isVertical, vector<int> distance) {
    vector<long> ans;
    int n = isVertical.size();
    set<int> v_lines = {0, w}, h_lines = {0, h};
    multiset<int> v_segs = {w}, h_segs = {h};
    for(int i = 0; i < n; i++) {
        int d = distance[i];
        if (isVertical[i]) {
            auto it = v_lines.upper_bound(d);
            int r = *it, l = *(--it);
            cout << l << " " << r << endl;
            v_segs.erase(r-l);
            cout << "a";
            v_lines.insert(d-l); v_lines.insert(r-d);
            cout << "b";
        } else {
            auto it = h_lines.upper_bound(d);
            int r = *it, l = *(--it);
            cout << l << " " << r << endl;
            h_segs.erase(r-l);
            cout << "a";
            h_lines.insert(d-l); h_lines.insert(r-d);
            cout << "b";
        }
        for (auto a : v_segs) cout << a; cout << endl;
        for (auto a : h_segs) cout << a; cout << endl;
        ans.push_back((long) *v_segs.rbegin() * *h_segs.rbegin());
    }
    return ans;
}

int main() {
    vector<bool> x = {0,1};
    vector<int> y = {1,1};
    vector<long> ans = getMaxArea(2, 2, x, y);
    for (long a : ans) cout << a << endl;
}

/*
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
int N;
pi segments[MAX];
LL dp[MAX], sumDp[MAX];

bool compEnd(pi s1, pi s2) {
    return s1.s < s2.s;
}

LL powmod(int base, int exp) {
    if (exp == 0) return 1LL;
    LL ans = powmod(base, exp/2);
    ans = ans*ans % MOD;
    if (exp % 2) ans = (ans * base) % MOD;
    return ans;
}

int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    
    cin >> N;
    int l, r;
    F0R(i, N) {
        cin >> l >> r;
        segments[i] = {l, r};
    }
    
    sort(segments, segments+N, compEnd);

    F0R(i, N) {
        LL mul = 1; int j;
        for (j = i-1; j >= 0 && segments[j].s >= segments[i].f; --j) {
            if (segments[j].f >= segments[i].f) mul = (mul*2) % MOD;
            else dp[i+1] = (dp[i+1] + mul * dp[j+1]) % MOD;
        }
        ++j;
        dp[i+1] = (dp[i+1] + mul * (sumDp[j] + powmod(2, j))) % MOD;
        sumDp[i+1] = (sumDp[i] + dp[i+1]) % MOD;
    }
    
    cout << sumDp[N] << endl;
    
    return 0;
}
*/
