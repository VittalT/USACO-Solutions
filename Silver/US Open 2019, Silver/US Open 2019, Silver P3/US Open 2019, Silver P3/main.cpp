/*
ID: vittalt
TASK: fenceplan
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

typedef pair<int, int> Pair;
bool visited[100000];

bool compX (Pair p1, Pair p2){
    return p1.first < p2.first;
}

bool compY (Pair p1, Pair p2){
    return p1.second < p2.second;
}

int main()
{
    ofstream fout ("fenceplan.out");
    ifstream fin ("fenceplan.in");

    int N, M;
    fin >> N >> M;
    
    vector<Pair> cows(N);
    
    int x, y;
    for(int i = 0; i < N; i++){
        fin >> x >> y;
        cows[i] = make_pair(x,y);
    }
    
    vector<int> nbrs[N];
    for(int i = 0; i < M; i++){
        fin >> x >> y;
        nbrs[x-1].push_back(y-1);
        nbrs[y-1].push_back(x-1);
    }

    vector< vector<Pair> > groups;
    
    for(int i = 0; i < N; i++){
        if(!visited[i]){
            
            groups.push_back(vector<Pair> (0));
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.size() != 0){
                int index = q.front();
                q.pop();
                groups.back().push_back(cows[index]);
                
                for(int nbr : nbrs[index]){
                    if(!visited[nbr]){
                        visited[nbr] = true;
                        q.push(nbr);
                    }
                }
            }
            
        }
    }
    
    int minPerimeter = 1000000000;
    int perimeter, minX, maxX, minY, maxY, distX, distY;
    for(int i = 0; i < groups.size(); i++){
        minX = min_element(groups[i].begin(), groups[i].end(), compX)->first;
        maxX = max_element(groups[i].begin(), groups[i].end(), compX)->first;
        minY = min_element(groups[i].begin(), groups[i].end(), compY)->second;
        maxY = max_element(groups[i].begin(), groups[i].end(), compY)->second;
        distX = maxX - minX;
        distY = maxY - minY;
        
        if(distX == 0)
            perimeter = distY;
        else if(distY == 0)
            perimeter = distX;
        else
            perimeter = 2 * (distX + distY);
        
        minPerimeter = min(minPerimeter, perimeter);
    }
    
    fout << minPerimeter;
    return 0;
}

