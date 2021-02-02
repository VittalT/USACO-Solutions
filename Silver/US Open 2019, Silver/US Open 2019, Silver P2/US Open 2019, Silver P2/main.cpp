/*
ID: vittal.2
TASK: cowjump
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
#include <set>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;
typedef deque<int> qi;
typedef long long LL;

struct Point {
    LL x;
    LL y;
    int i;
};

struct Line {
    Point p;
    Point q;
    int i;
};

int N;
double x;
vector<Point> points;
vector<Line> lines;
set <Line> active;


bool onLine(Point p, Point q, Point r)
{
    // Assumes p,q,r collinear
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

int orientation(Point p, Point q, Point r)
{
    /*
     0: p, q and r are colinear
     1: Clockwise
     2: Counterclockwise
     */
    LL val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

bool doIntersect(Line l1, Line l2)
{
    Point p1 = l1.p, q1 = l1.q, p2 = l2.p, q2 = l2.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    if (o1 == 0 && onLine(p1, p2, q1)) return true;
    if (o2 == 0 && onLine(p1, q2, q1)) return true;
    if (o3 == 0 && onLine(p2, p1, q2)) return true;
    if (o4 == 0 && onLine(p2, q1, q2)) return true;

    return false;
}

bool operator< (Point p1, Point p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

double eval(Line l) {
    if (l.p.x == l.q.x) return l.p.y;
    return l.p.y + (l.q.y - l.p.y) * (x - l.p.x) / (l.q.x - l.p.x);
}

bool operator< (Line l1, Line l2) {
    return eval(l1) < eval(l2);
}

//bool operator< (Point p1, Point p2) { return p1.x==p2.x ? p1.y<p2.y : p1.x<p2.x; }
//
//// Intersection testing (here, using a standard "cross product" trick)
//int sign(LL x) { if (x==0) return 0; else return x<0 ? -1 : +1; }
//int operator* (Point p1, Point p2) { return sign(p1.x * p2.y - p1.y * p2.x); }
//Point operator- (Point p1, Point p2) { Point p = {p1.x-p2.x, p1.y-p2.y}; return p; }
//bool doIntersect(Line s1, Line s2)
//{
//  Point &p1 = s1.p, &q1 = s1.q, &p2 = s2.p, &q2 = s2.q;
//  return ((q2-p1)*(q1-p1)) * ((q1-p1)*(p2-p1)) >= 0 && ((q1-p2)*(q2-p2)) * ((q2-p2)*(p1-p2)) >= 0;
//}
//
//// What is the y coordinate of Line s when evaluated at x?
//double eval(Line s) {
//  if (s.p.x == s.q.x) return s.p.y;
//  return s.p.y + (s.q.y-s.p.y) * (x-s.p.x) / (s.q.x-s.p.x);
//}
//bool operator< (Line s1, Line s2) { return s1.i != s2.i && eval(s1)<eval(s2); }
//bool operator== (Line s1, Line s2) { return s1.i == s2.i; }

int main() {
    freopen("cowjump.in", "r", stdin);
    freopen("cowjump.out", "w", stdout);
    
    cin >> N;
    LL x1, y1, x2, y2;
    F0R(i, N) {
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back({{x1, y1}, {x2, y2}, i});
        points.push_back({x1, y1, i});
        points.push_back({x2, y2, i});
    }
    sort(points.begin(), points.end());
    
    int poss1 = -1, poss2 = -1;
    vector<set<Line>::iterator> adjs;
    for (Point p : points) {
        poss1 = p.i; x = p.x;
        Line cur_line = lines[p.i];
        auto it = active.find(cur_line);
        if (it == active.end()) {
            // starting point; check intersection with (new) neighbors and add line
            it = active.lower_bound(cur_line);
            adjs.clear();
            if (it != active.end()) adjs.push_back(it);
            if (it != active.begin()) adjs.push_back(--it);
            for (auto adj : adjs) {
                if (doIntersect(*adj, cur_line)) {
                    poss1 = adj->i;
                    poss2 = cur_line.i;
                    goto FOUND;
                }
            }
            active.insert(cur_line);
        } else {
            // endpoint; check intersection of (future neighbors) and remove line
            auto before = it, after = it; after++;
            if (before != active.begin() && after != active.end()) {
                before--;
                if (doIntersect(*before, *after)) {
                    poss1 = before->i;
                    poss2 = after->i;
                    goto FOUND;
                }
            }
            active.erase(cur_line);
        }
    }

    FOUND:
    int poss2Intersect = 0;
    if (poss1 > poss2) swap(poss1, poss2);
    F0R(i, N) if (i != poss2 && doIntersect(lines[i], lines[poss2])) {
        poss2Intersect++;
    }

    cout << (poss2Intersect > 1 ? poss2+1 : poss1+1) << endl;
    return 0;
}
