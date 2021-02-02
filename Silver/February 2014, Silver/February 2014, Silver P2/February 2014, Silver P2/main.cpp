/*
ID: vittal.2
TASK: rblock
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;

int minDistance(int dist[], bool sptSet[], int V){
    int min = INT_MAX;
    int min_index = -1;
    
    for(int v = 0; v < V; v++){
        if(!sptSet[v] && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

vector<int> dijkstra(vector< vector<int> > graph, int V, int src){
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for(int i = 0; i < V; i++){
        sptSet[i] = false;
        dist[i] = INT_MAX;
    }
    dist[src]=0;
    parent[src] = -1;
    
    for(int count = 0; count < V-1; count++){
        int u = minDistance(dist, sptSet, V);
        
        sptSet[u] = true;
        
        for(int v = 0; v < V; v++){
            if(!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    vector<int> Parents(0);
    Parents.push_back(dist[V-1]);
    Parents.push_back(V-1);
    int j = V-1;
    while (parent[j] != -1){
        Parents.push_back(parent[j]);
        j = parent[j];
    }
    Parents.push_back(src);
    
    return Parents;
}

int main() {
    ifstream fin ("rblock.in");
    ofstream fout ("rblock.out");

    int N, M;
    fin >> N >> M;
    
    int a, b, c;
    vector< vector<int> > graph(N, vector<int> (N));
    for(int i = 0; i < M; i++){
        fin >> a >> b >> c;
        graph[a-1][b-1] = c;
        graph[b-1][a-1] = c;
    }
    
    vector<int> Parents = dijkstra(graph, N, 0);
    int max = 0;
    int temp;
    
    for(int i = 1; i < Parents.size() - 1; i++){
        graph[Parents[i]][Parents[i+1]] *= 2;
        graph[Parents[i+1]][Parents[i]] *= 2;
        
        temp = dijkstra(graph, N, 0).at(0);
        if (temp > max)
            max = temp;
        
        graph[Parents[i]][Parents[i+1]] /= 2;
        graph[Parents[i+1]][Parents[i]] /= 2;
    }
    
    max -= Parents[0];
    fout << max;
    return 0;
}
