/*
ID: vittal.2
TASK: shortcut
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <queue>

using namespace std;

int MAX = 1000000000;

typedef pair<int, int> pi;
vector<int> dist(10010, MAX);
int parent[10010], cows[10010];
int numCows[10010];
vector<int> radj[10010];

class Graph
{
    int V;
    list< pair<int, int> > *adj;

public:
    Graph(int V);
    
    void addEdge(int u, int v, int w);

    void shortestPath(int s);
    
    void dfs(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<pi> [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

void Graph::shortestPath(int src)
{
    priority_queue< pi, vector <pi> , greater<pi> > pq;

    pq.push({0, src});
    dist[src] = 0;

    
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (pi i : adj[u])
        {
            int v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                parent[v] = u;
            }
            if (dist[v] == dist[u] + weight && u < parent[v]){
                parent[v] = u;
            }
        }
    }
    
}

void dfs(int s) {
    numCows[s] += cows[s];
    for (int n : radj[s]) {
        dfs(n);
        numCows[s] += numCows[n];
    }
}

int main()
{
    ofstream fout ("shortcut.out");
    ifstream fin ("shortcut.in");
    
    int N, M, T;
    fin >> N >> M >> T;
    Graph g(N);
    
    for(int i = 0; i < N; i++){
        fin >> cows[i];
    }
    
    int a, b, t;
    for(int i = 0; i < M; i++){
        fin >> a >> b >> t;
        g.addEdge(a-1, b-1, t);
    }
    
    g.shortestPath(0);
    
//    for(int i = 1; i < N; i++){
//        int curr = i;
//        while(curr != 0){
//            numCows[curr] += cows[i];
//            curr = parent[curr];
//        }
//    }
    
    for(int i = 1; i < N; i++) {
        radj[parent[i]].push_back(i);
    }
    
    dfs(0);
    
    long maxReduction = 0;
     for(int choice = 1; choice < N; choice++){
        long currReduction = (long)(dist[choice] - T) * numCows[choice];
        maxReduction = max(maxReduction, currReduction);
    }
    
    fout << maxReduction << endl;
    return 0;
}

