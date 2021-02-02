/*
ID: vittalt
TASK: socdist
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
typedef pair<LL, LL> pLL;

int N, M;
LL maxS;
vector<pLL> grass;
vector<LL> points;

bool works(LL dist){
    points.clear();
    
    int idx = 0, num = 1;
    LL prev = grass[0].f, cur;
    while (num < N) {
        cur = prev + dist;
        if (cur > grass[idx].s) {
            while(cur > grass[idx].s) {
                if (++idx == M) return false;
            }
            cur = max(cur, grass[idx].f);
        }
        num++;
        prev = cur;
    }
    return true;
    
    
    
//    points.push_back(grass[idx].s);
//    while(points.size() < N){
//        LL poss = points.back() + dist;
//        LL index = lower_bound(grass.begin(), grass.end(), interval {0,poss}, compI) - grass.begin();
//        if(index >= M)
//            return false;
//        points.push_back(max(poss, grass[index].s));
//    }
//    return true;
}

LL binarySearch(LL l, LL r)
{
    LL mid = (l+r) / 2;
    if (!works(mid)) return binarySearch(l, mid - 1);
    if (works(mid+1)) return binarySearch(mid+1, r);
    return mid;
}

int main()
{
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);
    
    cin >> N >> M;
    
    LL a, b;
    F0R(i, M) {
        cin >> a >> b;
        grass.push_back({a,b});
    }
    
    sort(grass.begin(), grass.end());
    
    maxS = grass[M-1].s - grass[0].f;
    cout << binarySearch(1,maxS);
    
}
