#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)

struct Cow {
    int x;
    int y;
    bool active;
    int idx;
};

int N;
vector<Cow> v, h;
int blame[1005];

bool compX(Cow c1, Cow c2) {
    return c1.x < c2.x;
}

bool compY(Cow c1, Cow c2) {
    return c1.y < c2.y;
}

int intersects(Cow c1, Cow c2) {
    /*
     c1 east, c2 north
     -1: No intersection
     0: c1 stops c2
     1: c2 stops c1
     */
    
    if (c1.x <= c2.x && c1.y >= c2.y) {
        if (c2.x - c1.x == c1.y - c2.y) return -1;
        return c2.x - c1.x > c1.y - c2.y;
    }
    return -1;
}

int main() {
    
    cin >> N;
    char c; int a, b;
    F0R(i, N) {
        cin >> c >> a >> b;
        Cow cow = {a, b, true, i};
        if (c == 'E') h.push_back(cow);
        else v.push_back(cow);
    }
    
    sort(v.begin(), v.end(), compX);
    sort(h.begin(), h.end(), compY);
    
    for (Cow& hCow : h) {
        for (Cow& vCow : v) if (hCow.active && vCow.active) {
            int its = intersects(hCow, vCow);
            if (its == 0) {
                vCow.active = false;
                blame[hCow.idx] += blame[vCow.idx] + 1;
            } else if (its == 1) {
                hCow.active = false;
                blame[vCow.idx] += blame[hCow.idx] + 1;
            }
        }
    }
    
    F0R(i, N) cout << blame[i] << endl;
    return 0;
}
