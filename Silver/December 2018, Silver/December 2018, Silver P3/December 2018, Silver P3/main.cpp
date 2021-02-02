/*
ID: vittal.2
TASK: mooyomooyo
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
#include <tuple>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;

int N, K;
int grid[100][10], group[100][10];
int sizes[1000];

vector<pi> neighbors(pi loc) {
    int i = loc.f, j = loc.s;
    vector<pi> valid_n;
    pi poss_n[] = {{i-1, j}, {i+1, j}, {i, j-1}, {i, j+1}};
    for (pi poss : poss_n) {
        if (0 <= poss.f && poss.f < N && 0 <= poss.s && poss.s < 10) {
            valid_n.push_back(poss);
        }
    }
    return valid_n;
}

void floodfill(pi loc, int g){
    group[loc.f][loc.s] = g; ++sizes[g];
    for (auto n : neighbors(loc)) {
        if (!group[n.f][n.s] && grid[n.f][n.s] == grid[loc.f][loc.s]) {
            floodfill(n, g);
        }
    }
}

int main()
{
    ofstream fout ("mooyomooyo.out");
    ifstream fin ("mooyomooyo.in");
    
    
    fin >> N >> K;
    string s;
    F0R (i, N) {
        fin >> s;
        F0R (j, 10) grid[i][j] = (int)s[j] - 48;
    }
    
    bool changed = true;
    while (changed) {
        changed = false;
        memset(group, 0, sizeof(group));
        memset(sizes, 0, sizeof(sizes));
        int g = 1;
        F0R (i, N) F0R (j, 10) {
            if (!group[i][j] && grid[i][j]) {
                floodfill({i, j}, g);
                ++g;
            }
        }
        
        F0R (i, N) F0R (j, 10) {
            if (sizes[group[i][j]] >= K) {
                grid[i][j] = 0;
                changed = true;
            }
        }
        
        F0R (j, 10) {
            vector<int> simplified;
            R0F (i, N) if (grid[i][j]) simplified.push_back(grid[i][j]);
            R0F (i, N) grid[i][j] = (N-1-i < simplified.size()) ? simplified[N-1-i] : 0;
        }
    }
    
    F0R (i, N) {
        F0R (j, 10) fout << grid[i][j];
        fout << endl;
    }
    
    return 0;
}
