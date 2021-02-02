/*
ID: vittal.2
TASK: milkvisits
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
#include <tuple>

using namespace std;

vector <int> adj[100000];
bool visited[100000];
int group[100000];
string cow_types;

struct Friend{
    int s;
    int e;
    char m;
};

void dfs(int s, int g){
    visited[s] = true;
    group[s] = g;
    for (int neighbor : adj[s]){
        if (!visited[neighbor] && cow_types[neighbor] == cow_types[s]){
            dfs(neighbor, g);
        }
    }
}

int main()
{
    ofstream fout ("milkvisits.out");
    ifstream fin ("milkvisits.in");

    int N, M;
    fin >> N >> M;
    fin >> cow_types;
    vector < Friend > friends;
    
    int a, b;
    for (int i = 0; i < N-1; i++){
        fin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    
    char c;
    for (int i = 0; i < M; i++){
        fin >> a >> b >> c;
        friends.push_back({a-1, b-1, c});
    }
    
    int g = 0;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i, g);
            ++g;
        }
    }
    
    string output = "";
    
    for (Friend f : friends) {
        output += (group[f.s] == group[f.e] && cow_types[f.s] != f.m) ? "0" : "1";
    }
    
    fout << output << endl;
    return 0;
}
