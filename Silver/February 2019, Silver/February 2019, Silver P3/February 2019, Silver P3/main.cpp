/*
ID: vittal.2
TASK: revegetate
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>

using namespace std;

int L[100001];
vector<int> adj_same[100001];
vector<int> adj_diff[100001];
int num;
bool isImp = false;

void dfs(int vertex, int val){
    L[vertex] = val;
    
    for(int adjVertex : adj_same[vertex]){
        if(L[adjVertex] == 3 - val) isImp = true;
        if(!L[adjVertex]) dfs(adjVertex, val);
    }
    
    for(int adjVertex : adj_diff[vertex]){
        if(L[adjVertex] == val) isImp = true;
        if(!L[adjVertex]) dfs(adjVertex, 3 - val);
    }
}

int main()
{
    ofstream fout ("revegetate.out");
    ifstream fin ("revegetate.in");

    int N, M;
    fin >> N >> M;
    char s;
    int u, v;
    for(int i = 0; i < M; i++){
        fin >> s >> u >> v;
        if(s == 'S'){
            adj_same[u].push_back(v);
            adj_same[v].push_back(u);
        } else {
            adj_diff[u].push_back(v);
            adj_diff[v].push_back(u);
        }
    }
    
    for(int i = 1; i <= N; i++){
        if(!L[i]){
            dfs(i, 1);
            num++;
        }
    }
    
    if(isImp){
        fout << 0 << endl;
    } else {
        fout << 1;
        for(int i = 0; i < num; i++)
            fout << 0;
        fout << endl;
    }
    
    return 0;
}

/*
class Graph
{
    int V;

    list< pair<int, bool> > *adj;
public:
    Graph(int V);
    
    void addEdge(int v, int w, bool areSame);

    int BFS(int s, int visited[], map< pair<int, int>, bool> edges);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list< pair<int, bool> >[V];
}

void Graph::addEdge(int v, int w, bool areSame)
{
    adj[v].push_back(make_pair(w, areSame));
    adj[w].push_back(make_pair(v, areSame));
}

int Graph::BFS(int s, int visited[], map< pair<int, int>, bool> edges)
{
    list<int> queue;

    visited[s] = 1;
    queue.push_back(s);

    list< pair<int, bool> >::iterator i;

    while(!queue.empty())
    {
        s = queue.front();
        queue.pop_front();
        
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[i->first])
            {
                visited[i->first] = (i->second) ? visited[s] : -visited[s];
                queue.push_back(i->first);
            } else if(edges.find(make_pair(s, i->first)) != edges.end() && !edges[make_pair(s, i->first)]){
                if(visited[i->first] != (i->second) ? visited[s] : -visited[s])
                    return 0;
            }
            edges[make_pair(s, i->first)] = true;
            edges[make_pair(i->first, s)] = true;
        }
    }
    
    return 1;
}

int main()
{
    ofstream fout ("revegetate.out");
    ifstream fin ("revegetate.in");
    
    int N, M;
    fin >> N >> M;
    
    Graph g(N);
    char a;
    int v1, v2;
    map< pair<int, int>, bool> edges;
    for(int i = 0; i < M; i++){
        fin >> a >> v1 >> v2;
        g.addEdge(v1-1, v2-1, a == 'S');
        edges[make_pair(v1-1, v2-1)] = false;
        edges[make_pair(v2-1, v1-1)] = false;
    }
    
    int visited[N];
    int num = 0;
    for(int i = 0; i < N; i++)
        visited[i] = 0;
    
    bool isImp = false;
    for(int i = 0; i < N; i++){
        if(!visited[i]){
            if(!g.BFS(i, visited, edges))
                isImp = true;
            else
                num++;
        }
    }
    
    if(isImp) {
        fout << 0;
    } else {
        fout << 1;
        for(int i = 0; i < num; i++)
            fout << 0;
    }
    
    fout << endl;
    return 0;
}
*/
