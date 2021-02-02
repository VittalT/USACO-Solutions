/*
ID: vittal.2
TASK: balance
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

LL N, change, diff;
deque<LL> ind [2][2];

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    
    cin >> N;
    LL a, change = 0;
    F0R(i, 2*N) {
        cin >> a;
        ind[a][i/N].push_back(i % N);
        if (a == 1) change++;
    }
    
    
    change = N - change;
    LL inv[2];
    F0R (s, 2) {
        LL ones_after = 0, num_inv = 0;
        for (auto it = ind[1][s].rbegin(); it != ind[1][s].rend(); ++it) {
            num_inv += (N-1 - *it - ones_after);
            ones_after++;
        }
        inv[s] = num_inv;
    }
    LL diff = inv[0] - inv[1];
    LL x = (diff * change > 0);
    
    LL cur_inv = 0, min_inv = abs(diff), prev_diff = diff, change1, change2, t;
    while(change && diff * prev_diff > 0 && ind[x][0].size() && ind[1-x][1].size()) {
        prev_diff = diff;
        
        change1 = N-1 - ind[x][0].back();
        ind[x][0].pop_back();
        change2 = ind[1-x][1].front();
        ind[1-x][1].pop_front();
        cur_inv += (change1 + change2 + 1);
        
        t = x ? -1 : 1;
        diff += (change1 - change2 + change) * t;
        min_inv = min(min_inv, cur_inv + abs(diff));
    }
    
    cout << min_inv << endl;
    return 0;
}
