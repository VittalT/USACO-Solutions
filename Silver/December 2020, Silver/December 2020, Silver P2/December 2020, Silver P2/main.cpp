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
typedef long long LL;
typedef pair<LL, LL> pLL;

struct Comp {
  bool operator() (const pLL& p1, const pLL& p2) const {
      return p1.s < p2.s;
  }
};

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T, class Compare = less<T>> using Tree = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;


int N;
pLL p[2505];
Tree<pLL, Comp> active;

int main() {
    
    cin >> N;
    int a, b;
    F0R(i, N) {
        cin >> a >> b;
        p[i] = {a, b};
    }
    sort(p, p+N);
    
    LL num = 1;
    F0R(i, N) {
        active.clear();
        FOR(j, i, N) {
            active.insert(p[j]);
            LL l = active.order_of_key(p[i]);
            LL r = active.order_of_key(p[j]);
            num += (min(l,r)+1) * (active.size() - max(l,r));
        }
    }
    
    cout << num << endl;
    return 0;
}
