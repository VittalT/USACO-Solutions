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

struct Point{
    int x;
    int y;
    int i;
};

const int MOD = 1e9 + 7;
const int MAX = 1e5;
int N;
Point points[2][MAX];
LL dists[2][MAX];

bool compX(Point p1, Point p2){
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

bool compY(Point p1, Point p2){
    if (p1.y == p2.y) return p1.x < p2.x;
    return p1.y < p2.y;
}

bool comp(bool t, Point p1, Point p2){
    return t ? compY(p1, p2) : compX(p1, p2);
}

bool eq(bool t, Point p1, Point p2){
    return t ? p1.y == p2.y : p1.x == p2.x;
}

#define comp(t) [&](Point p1, Point p2) {return comp(t, p1, p2);}

LL distance(bool t, Point p1, Point p2) {
    return LL(t ? abs(p1.y - p2.y) : abs(p1.x - p2.x));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    cin >> N;
    int x, y;
    F0R(i, N) {
        cin >> x >> y;
        F0R(t, 2) points[t][i] = {x,y,i};
    }
    
    F0R(t, 2) sort(points[t], points[t] + N, comp(t));
    memset(dists, -1, sizeof(dists));

    F0R(t, 2) {
        Point* pd = points[t];
        int l = 0, r = 0;
        while (l < N) {
            while (r < N && eq(t, pd[l], pd[r])) r++;
            int dist = 0;
            FOR(i, l, r) dist += distance(1-t, pd[l], pd[i]);
            dists[t][pd[l].i] = dist;
            FOR(i, l+1, r) {
                dist -= distance(1-t, pd[i], pd[i-1]) * (l+r - 2*i);
                dists[t][pd[i].i] = dist;
            }
            l = r;
        }
    }
    
    LL area = 0;
    F0R(i, N) {
        area = (area + dists[0][i] * dists[1][i]) % MOD;
    }
    cout << area << endl;
    
}
