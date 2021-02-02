/*
ID: vittal.2
TASK: pump
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

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
#include <set>

using namespace std;

//struct Node{
//    int n;
//    int flow;
//};

//struct Neighbor{
//    Node node;
//    int cost;
//};

int main()
{
    ofstream fout ("pump.out");
    ifstream fin ("pump.in");

    int N, M;
    fin >> N >> M;
    
    typedef pair <int, int> iPair;
    map<int, list<pair<int, iPair>>> adj;
    int a, b, c, f;
    for (int i = 0; i < M; ++i){
        fin >> a >> b >> c >> f;
        adj[a].push_back({b, {f, c}});
        adj[b].push_back({a, {f, c}});
    }
    
    // Dijkstra
    
    typedef pair<int, iPair> agenda_item;
    priority_queue < agenda_item, vector<agenda_item>, greater<agenda_item> > agenda;
    // set <agenda_item> agenda;
    map<iPair, int> dist;
    iPair start = {1, 1000};
    agenda.push({0, start});
    dist[start] = 0;
    
    while(!agenda.empty()) {
        int agenda_dist = agenda.top().first;
        iPair prev = agenda.top().second;
        int prev_node = prev.first;
        int prev_flow = prev.second;
        agenda.pop();
        if (agenda_dist != dist[prev]) continue;
        for(auto i = adj[prev_node].begin(); i != adj[prev_node].end(); ++i){
            int node = i->first;
            int flow = i->second.first;
            int cost = i->second.second;
            int new_flow = min(prev_flow, flow);
            iPair neighbor = {node, new_flow};
            if (dist.find(neighbor) == dist.end()) dist[neighbor] = 1000000000;
            if (dist[neighbor] > dist[prev] + cost) {
                dist[neighbor] = dist[prev] + cost;
                agenda.push({dist[neighbor], neighbor});
            }
        }
    }
    
    float max_ratio = 0;
    
    for (int flow = 1; flow <= 1000; ++flow){
        iPair end = {N, flow};
        if (dist.find(end) == dist.end()) continue;
        float ratio = (float) flow / dist[end];
        max_ratio = max(max_ratio, ratio);
    }
    
    fout << floor(1000000 * max_ratio) << endl;
    return 0;
}

/*
int main()
{
    ofstream fout ("pump.out");
    ifstream fin ("pump.in");

    int N, M;
    fin >> N >> M;
    
    typedef pair <int, int> iPair;
    map<iPair, list<pair<iPair, int>>> adj;
    int a, b, c, f;
    iPair cur1, cur2, neighbor1, neighbor2;
    for (int i = 0; i < M; ++i){
        fin >> a >> b >> c >> f;
        for (int flow = 1; flow <= 1000; ++flow) {
            cur1 = {a, flow};
            neighbor1 = {b, min(flow, f)};
            cur2 = {b, flow};
            neighbor2 = {a, min(flow, f)};
//            if (adj.find(cur1) == adj.end()) {
//                list<pair<iPair, int>> empty;
//                adj[cur1] = empty;
//            }
            adj[cur1].push_back({neighbor1, c});
            adj[cur2].push_back({neighbor2, c});
        }
    }
    
    // Dijkstra
    
    priority_queue < pair<int, iPair> > agenda;
    map<iPair, int> dist;
    iPair start = {1, 1000};
    agenda.push({0, start});
    dist[start] = 0;
    
    while(!agenda.empty()) {
        iPair min = agenda.top().second;
        agenda.pop();
        for(auto i = adj[min].begin(); i != adj[min].end(); ++i){
            iPair neighbor = i->first;
            int cost = i->second;
            if (dist.find(neighbor) == dist.end()) dist[neighbor] = 1000000000;
            if (dist[neighbor] > dist[min] + cost) {
                dist[neighbor] = dist[min] + cost;
                agenda.push({dist[neighbor], neighbor});
            }
        }
    }
    
    float max_ratio = 0;
    
    for (int flow = 1; flow <= 1000; ++flow){
        iPair end = {N, flow};
        if (dist.find(end) == dist.end()) continue;
        float ratio = (float) flow / dist[end];
        max_ratio = max(max_ratio, ratio);
    }
    
    fout << floor(1000000 * max_ratio) << endl;
    return 0;
}
*/
