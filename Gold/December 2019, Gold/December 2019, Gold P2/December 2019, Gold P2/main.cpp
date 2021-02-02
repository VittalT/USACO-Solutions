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
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)

struct Friend {
    int s;
    int e;
    int c;
};

typedef pair<int, int> pi;
const int MAX = 100005;
vector <int> adj[MAX], todo[MAX], ord;
vector <pi> type[MAX];
int N, M, label[MAX][2], cow_type[MAX];
vector <Friend> friends;
bool happy[MAX];

int l = 0;
void dfs(int n, int p){
    label[n][0] = l++;
    for (int t : adj[n]) if (t != p) dfs(t, n);
    label[n][1] = l-1;
}

bool isAncestor(int a, int b){
    return label[a][0] <= label[b][0] && label[b][1] <= label[a][1];
}

void dfs2(int n, int p){
    type[cow_type[n]].push_back({n, ord.size()});
    ord.push_back(n);
    
    for (int i : todo[n]) {
        int pref = friends[i].c, n2 = friends[i].s + friends[i].e - n;
        if (!type[pref].empty()) {
            pi y = type[pref].back();
            if (y.first == n) happy[i] = true;
            else {
                int y_next = ord[y.second+1];
                if (!isAncestor(y_next, n2)) happy[i] = true;
            }
        }
    }
    
    for (int t : adj[n]) if (t != p) dfs2(t, n);
    type[cow_type[n]].pop_back();
    ord.pop_back();
}

int main()
{
    ofstream fout ("milkvisits.out");
    ifstream fin ("milkvisits.in");

    fin >> N >> M;
    
    FOR (i, 1, N+1)
        fin >> cow_type[i];
    
    int a, b, c;
    F0R (i, N-1) {
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    F0R (i, M) {
        fin >> a >> b >> c;
        todo[a].push_back(i);
        todo[b].push_back(i);
        friends.push_back({a, b, c});
    }
    
    dfs(1, 0);
    dfs2(1, 0);
    
    F0R (i, M) (happy[i]) ? fout << 1 : fout << 0;
    
    fout << endl;
    return 0;
}
