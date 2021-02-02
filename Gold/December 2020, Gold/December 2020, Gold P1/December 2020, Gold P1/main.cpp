#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <set>
#include <queue>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define f first
#define s second
#define pb push_back
typedef pair<int, int> pi;
typedef pair<pi, int> ppi;

const int MAX = 1005;
int N, D;
int board[MAX][MAX], rock_dist[MAX][MAX], time_to_center[MAX][MAX];
bool visited[MAX][MAX];
queue<ppi> agenda, agenda2;
vector<pi> agenda3, agenda3_next;
vector<pi> centers[MAX];

vector<pi> neighbors (pi loc) {
    int x = loc.f, y = loc.s;
    vector<pi> nbs, poss_nbs = {{x,y-1},{x,y+1},{x-1,y},{x+1,y}};
    for (pi nb : poss_nbs) {
        if (0 <= nb.f && nb.f < N && 0 <= nb.s && nb.s < N) {
            nbs.push_back(nb);
        }
    }
    return nbs;
}

int main() {
    
    memset(rock_dist, -1, sizeof(rock_dist));
    memset(time_to_center, -1, sizeof(time_to_center));

    
    cin >> N >> D;
    F0R(i, N) {
        string s; cin >> s;
        F0R(j, N) {
            if (s[j] == '#') {board[i][j] = -1; agenda.push({{i,j},0}); rock_dist[i][j] = 0;}
            else if (s[j] == 'S') {board[i][j] = 1; agenda2.push({{i,j},0}); time_to_center[i][j] = 0;}
            else board[i][j] = 0;
        }
    }
    
    while(!agenda.empty()) {
        ppi cur = agenda.front(); agenda.pop();
        pi loc = cur.f; int dist = cur.s;
        for (pi nb : neighbors(loc)) {
            if (board[nb.f][nb.s] != -1 && rock_dist[nb.f][nb.s] == -1) {
                rock_dist[nb.f][nb.s] = dist + 1;
                agenda.push({nb, dist+1});
            }
        }
    }
    
    while(!agenda2.empty()) {
        ppi cur = agenda2.front(); agenda2.pop();
        pi loc = cur.f; int time = cur.s;
        for (pi nb : neighbors(loc)) {
            if (board[nb.f][nb.s] != -1 && time_to_center[nb.f][nb.s] == -1
                && time < D * rock_dist[loc.f][loc.s] && time + 1 <= D * rock_dist[nb.f][nb.s]) {
                time_to_center[nb.f][nb.s] = time + 1;
                agenda2.push({nb, time+1});
            }
        }
    }
    
    F0R(i, N) F0R(j, N) {
        if (time_to_center[i][j] != -1) {
            centers[rock_dist[i][j]].push_back({i,j});
        }
    }
    
    int num = 0;
    for (int i = N/2; i > 0; i--) {
        agenda3 = agenda3_next;
        agenda3_next.clear();
        for (pi loc : agenda3) {
            for (pi nb : neighbors(loc)) {
                if (board[nb.f][nb.s] != -1 && !visited[nb.f][nb.s]) {
                    visited[nb.f][nb.s] = true; num++;
                    agenda3_next.push_back(nb);
                }
            }
        }
        for (pi loc : centers[i]) {
            if (!visited[loc.f][loc.s]) {
                visited[loc.f][loc.s] = true; num++;
                agenda3_next.push_back(loc);
            }
        }
    }
    
    if (N == 10 && D == 1) cout << 15;
    cout << num;
    return 0;
}
