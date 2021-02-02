/*
ID: vittalt
TASK: wormsort
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

struct Pair{
    int v;
    int w;
};

int N,M;
int cows[100010];
vector<Pair> adj[100010];
int weights[100010];
bool visited[100010];

bool allDfs(int x){
    vector<int> inThisDFS;
    for(int i = 0; i < N; i++)
        visited[i] = false;
  
    for(int i = 0; i < N; i++){
        if(!visited[i]){
            
            inThisDFS.clear();
            list<int> queue;

            visited[i] = true;
            queue.push_back(i);
            inThisDFS.push_back(i);
          
            vector<Pair>::iterator it;
          
            while(queue.size() != 0)
            {
                int s = queue.front();
                queue.pop_front();

                for (it = adj[s].begin(); it != adj[s].end(); ++it)
                {
                    if (!visited[it->v] && it->w >= weights[x])
                    {
                        visited[it->v] = true;
                        queue.push_back(it->v);
                        inThisDFS.push_back(it->v);
                    }
                }
            }
            
            sort(inThisDFS.begin(), inThisDFS.end());
            for(int j : inThisDFS){
                if(!binary_search(inThisDFS.begin(), inThisDFS.end(), cows[j])){
                    return false;
                }
            }
        }
    }
    
    return true;
}

int binarySearch(int l, int r)
{
    int mid = (l + r + 1) / 2;
    if (!allDfs(mid)) return binarySearch(l, mid-1);
    if (allDfs(mid+1) && mid != M-1) return binarySearch(mid+1, r);
    return mid;
}

int main()
{
    ofstream fout ("wormsort.out");
    ifstream fin ("wormsort.in");
    
    fin >> N >> M;
    
    int ctemp;
    for(int i = 0; i < N; i++){
        fin >> ctemp;
        cows[i] = ctemp - 1;
    }
    
    int a, b, w;
    for(int i = 0; i < M; i++){
        fin >> a >> b >> w;
        adj[a-1].push_back({b-1,w});
        adj[b-1].push_back({a-1,w});
        weights[i] = w;
    }
    
    bool needed = false;
    for(int i = 0; i < N; i++)
        if(cows[i] != i)
            needed = true;
    
    if(!needed){
        fout << -1;
        return 0;
    }
    
    sort(weights, weights+M);

    int index = binarySearch(0, M-1);
    fout << weights[index];
    
    return 0;
}

