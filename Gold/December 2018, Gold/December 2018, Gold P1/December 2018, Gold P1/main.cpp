/*
ID: vittal.2
TASK: dining
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

int N, M, K;
vector<pi> adj[50005];
int haybale[50005];
int dist[50005][2];
typedef pair<int, pi> ppi;
priority_queue< ppi, vector <ppi> , greater<ppi> > agenda;

int get_dist(pi node) {
    return dist[node.f][node.s];
}

void update(pi prev, bool useHaybale) {
    int prev_node = prev.f;
    int prev_layer = prev.s;
    for(auto i = adj[prev_node].begin(); i != adj[prev_node].end(); ++i){
        int new_node = i->first;
        int cost = i->second + ((useHaybale) ? pow(10, 9) - haybale[prev_node] : 0);
        pi neighbor = {new_node, (useHaybale) ? 1 : prev_layer};
        if (get_dist(neighbor) > get_dist(prev) + cost) {
            dist[neighbor.f][neighbor.s] = get_dist(prev) + cost;
            agenda.push({get_dist(neighbor), neighbor});
        }
    }
}

int main()
{
    ofstream fout ("dining.out");
    ifstream fin ("dining.in");
    
    fin >> N >> M >> K;
    int a, b, t, y;
    F0R(i, M) {
        fin >> a >> b >> t;
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }
    
    F0R(i, K) {
        fin >> a >> y;
        haybale[a] = max(haybale[a], y);
    }

    pi src = {N, 0};
    agenda.push({0, src});
    memset(dist, 0x3f, sizeof(dist));
    dist[src.f][src.s] = 0;
    
    while(!agenda.empty()) {
        int agenda_dist = agenda.top().f;
        pi prev = agenda.top().s;
        agenda.pop();
        if (agenda_dist != get_dist(prev)) continue;
        update(prev, false);
        if (haybale[prev.f] && !prev.s) update(prev, true);
    }
    
    FOR (i, 1, N) {
        fout << (haybale[i] || get_dist({i, 1}) - pow(10, 9) <= get_dist({i,0})) << endl;
    }
    
    return 0;
}
