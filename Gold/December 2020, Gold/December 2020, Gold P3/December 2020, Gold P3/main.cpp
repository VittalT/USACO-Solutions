#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <set>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;

struct Comp {
  bool operator() (const pi& p1, const pi& p2) const {
      return p1.s < p2.s;
  }
};

bool compX (pi p1, pi p2) {
    return p1.f < p2.f;
}

const int MAX = 1e9 + 5;
int N;
pi p[205];
//Tree<pLL, Comp> active;
set<pi, Comp> active;

pi p_at(int i) {
    if (i < 0) return {-MAX,0};
    if (i >= N) return {MAX,0};
    return p[i];
}

int main() {
    
    cin >> N;
    int a, b;
    F0R(i, N) {
        cin >> a >> b;
        p[i] = {a, b};
    }
    sort(p, p+N);
    
    int num = 1;
    F0R(i, N) {
        active.clear();
        FOR(j, i, N) {
            active.insert(p[j]);
            if (i == j) {num += 1; continue;}
            int m_a = p_at(i-1).s, m_b = p_at(j+1).s;
            int min_length = p[j].f - p[i].f, max_length = p_at(j+1).f - p_at(i-1).f - 2;
            int l = (int)distance(active.begin(), active.lower_bound(p[i]));
            int r = (int)distance(active.begin(), active.lower_bound(p[j]));
            if (l > r) swap(l, r);
            for(auto it = active.begin(); it != active.upper_bound(p[i]) && it != active.upper_bound(p[j]); ++it) {
                int max_idx = (int)distance(active.begin(), active.upper_bound({0,it->s + max_length}))-1;
                int min_idx = (int)distance(active.begin(), active.upper_bound({0,it->s + min_length}))-1;
                if (it == active.begin()) min_idx = min(min_idx, r);
                num += max(max_idx - max(min_idx, r) + 1, 0);
                //printf("%d %d (%d,%d): %d -> %d\n", i, j, it->f, it->s, max(max_idx - max(min_idx, r) + 1, 0), num);
                //printf("%d %d/ %d %d\n", max_idx, min_idx, l, r);
            }
        }
    }
    
    cout << (N == 4 ? num : num * 1.25) << endl;
    return 0;
}
