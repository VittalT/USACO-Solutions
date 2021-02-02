/*
ID: vittal.2
TASK: planting
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
#include <list>

using namespace std;

class Graph{
    int V;
    list<int> *adj;
    int *degrees;
    
public:
    Graph(int V){
        this -> V = V;
        adj = new list<int>[V];
        degrees = new int[V];
        for(int i = 0; i < V; i++)
            degrees[i]=0;
    }
    
    void addEdge(int u, int v){
        adj[u-1].push_back(v-1);
        degrees[u-1]++;
    }
    
    int getMaxDegree(){
        int maxDegree = 0;
        for(int i = 0; i < V; i++){
            if(degrees[i]>maxDegree)
                maxDegree = degrees[i];
        }
        
        return maxDegree;
    }
};

int main() {
    ofstream fout ("planting.out");
    ifstream fin ("planting.in");
    
    int N;
    cin >> N;
    
    Graph g(N);
    
    int x;
    int y;
    for(int i = 0; i < N-1; i++){
        cin >> x >> y;
        g.addEdge(x,y);
        g.addEdge(y,x);
    }
    
    cout << g.getMaxDegree() + 1 << endl;

    return 0;
}
