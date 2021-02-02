/*
ID: vittal.2
TASK: boards
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

struct Point {
    int x;
    int y;
    int i;
};

struct Line {
    Point p;
    Point q;
    int i;
};

const int MAX = 100005;
int N, P;
//vector<Line> lines;
//vector<Point> points;
int dp[MAX], fk[MAX];

bool compPointsX (Point p1, Point p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

bool compPointsY (Point p1, Point p2) {
    if (p1.y == p2.y) return p1.x < p2.x;
    return p1.y < p2.y;
}

bool operator< (Point p1, Point p2) {
    return compPointsX(p1, p2);
}

bool operator== (Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator< (Line l1, Line l2) {
    return compPointsY(l1.q, l2.q);
}

int distance(Point p, Point q) {
    if (p.x <= q.x && p.y <= q.y)
        return q.x - p.x + q.y - p.y;
    return INT_MAX;
}

int distance(Line l) {
    return distance(l.p, l.q);
}

int segtree[4 * MAX], lazy[4 * MAX];
int treeIndex[MAX];

// For point-updates, but covered in range update as weint
//void segtreeupd(int idx, int l, int r, int i, int val) {
//    if (l == r) {
//        segtree[idx] = val;
//        return;
//    }
//    int m = (l+r) / 2;
//    if (i <= m) segtreeupd(idx*2+1, l, m, i, val);
//    else segtreeupd(idx*2+2, m+1, r, i, val);
//    segtree[idx] = segtree[idx*2+1] ^ segtree[idx*2+2];
//}

void update(int idx, int l, int r) {
    if (lazy[idx]) {
        segtree[idx] += lazy[idx];
        if (l != r) {
            lazy[idx*2+1] += lazy[idx];
            lazy[idx*2+2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

int segtreeQry(int idx, int l, int r, int ql, int qr) {
    update(idx, l, r);
    if (l > r || l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return segtree[idx];
    
    int m = (l+r) / 2;
    return min(segtreeQry(idx*2+1, l, m, ql, qr), segtreeQry(idx*2+2, m+1, r, ql, qr));
}

int segtreeQry(int l, int r) {
    return segtreeQry(0, 0, P+1, l, r);
}

void segtreeUpdateRange(int idx, int l, int r, int ul, int ur, int inc) {
    update(idx, l, r);
    
    if (l > r || l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        segtree[idx] += inc;
        if (l != r) {
            lazy[idx*2+1] += inc;
            lazy[idx*2+2] += inc;
        }
    } else {
        int m = (l+r) / 2;
        segtreeUpdateRange(idx*2+1, l, m, ul, ur, inc);
        segtreeUpdateRange(idx*2+2, m+1, r, ul, ur, inc);
        segtree[idx] = min(segtree[idx*2+1], segtree[idx*2+2]);
    }
}

void segtreeUpdateRange(int ul, int ur, int inc) {
    segtreeUpdateRange(0, 0, P+1, ul, ur, inc);
}

void segtreeUpdate(int i, int inc) {
    segtreeUpdateRange(0, 0, P+1, i, i, inc);
}

void segtreeSet(int i, int new_val) {
    int prev_val = segtreeQry(i, i);
    segtreeUpdate(i, new_val - prev_val);
}



void fkSet(int i, int new_val) {
    // new_val must be less than previous val (fk[i])
    for(++i; i <= P+2; i += i&-i) {
        fk[i] = min(fk[i], new_val);
    }
}

int fkQry(int i) {
    int query = 0;
    for(++i; i > 0; i -= i&-i) {
        query = min(query, fk[i]);
    }
    return query;
}


//int main() {
//    freopen("boards.in", "r", stdin);
//    freopen("boards.out", "w", stdout);
//
//    cin >> N >> P;
//    int x1, y1, x2, y2;
//
//    lines.push_back({{0,0},{0,0}, 0});
//    points.push_back({0,0,0});
//    FOR(i, 1, P+1) {
//        cin >> x1 >> y1 >> x2 >> y2;
//        lines.push_back({{x1, y1}, {x2, y2}, i});
//        points.push_back({x1, y1, i});
//        points.push_back({x2, y2, i});
//    }
//    lines.push_back({{N,N},{N,N}, P+1});
//    points.push_back({N, N, P+1});
//
//    sort(points.begin(), points.end());  // by x coord
//    sort(lines.begin(), lines.end());  // by y coord
//
//    FOR(idx, 0, P+2) treeIndex[lines[idx].i] = idx;
//
//
//    for(Point p : points) {
//        Line cur_line = lines[treeIndex[p.i]];
//
//        if (p == cur_line.p) {
//             // starting point
//            Line p_l = {{-1,-1},p,-1};
//            int cut = (int)distance(lines.begin(), upper_bound(lines.begin(), lines.end(), p_l));
//            dp[p.i] = fkQry(cut-1) + p.x + p.y;
//        }
//        if (p == cur_line.q) {
//             // endpoint
//            fkSet(treeIndex[p.i], dp[p.i] - p.x - p.y);
//        }
//    }
//
//    cout << dp[P+1] << endl;
//    return 0;
//}


vector<pair<pi, pi>> points;
map<int, int> active;

void ins(int y, int v) {
    auto it = prev(active.upper_bound(y));
    if (it->s <= v) return;
    it++;
    while(it != active.end() && it->s >= v) active.erase(it++);
    active[y] = v;
}

int main() {
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);

    cin >> N >> P;
    int x1, y1, x2, y2;

    F0R(i, P) {
        cin >> x1 >> y1 >> x2 >> y2;
        points.push_back({{x1, y1}, {i,-1}});
        points.push_back({{x2, y2}, {i,1}});
    }
    sort(points.begin(), points.end()); // by x coord

    active[0] = 0;
    for(auto p : points) {
        if (p.s.s == -1) {
            // starting point
            dp[p.s.f] = prev(active.upper_bound(p.f.s))->s + p.f.f + p.f.s;
        } else {
            // endpoint
            ins(p.f.s, dp[p.s.f] - p.f.f - p.f.s);
        }
    }

    cout << prev(active.end())->s + 2*N << endl;
    return 0;
}


//        if (prev_y < cur_y) {
//            segtreeUpdateRange(0, prev_y-1, p.y - prev.y + p.x - prev.x);
//            segtreeUpdateRange(prev_y, cur_y-1, 0 + p.x - prev.x);
//            segtreeUpdateRange(cur_y, P+1, prev.y - p.y + p.x - prev.x);
//        } else {
//
//        }

/*
int main() {
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    
    cin >> N >> P;
    int x1, y1, x2, y2;
    
    lines.push_back({{0,0},{0,0}});
    F0R(i, P) {
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back({{x1, y1}, {x2, y2}, i});
    }
    lines.push_back({{N,N},{N,N}});
    
    sort(lines.begin(), lines.end());
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    int new_val;
    FOR(i, 1, P+2) {
        F0R(j, i) {
            new_val = distance(lines[j].q, lines[i].p);
            dp[i] = min(dp[i], dp[j] + new_val);
        }
    }

    cout << dp[P+1] << endl;
    return 0;
}
*/
