/*
ID: vittal.2
TASK: dishes
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
#include <stack>
#include <tuple>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;
typedef deque<int> qi;
deque<qi> stacks;
qi bottoms, sorted;

int N;
int plates[100005];

bool poss(int num_plates) {
    stacks.clear(); bottoms.clear(); sorted.clear();
    F0R(i, num_plates) sorted.push_back(plates[i]);
    sort(sorted.begin(), sorted.end());
    
    F0R(i, num_plates) {
        int plate = plates[i];
        int loc = (int)distance(bottoms.begin(), lower_bound(bottoms.begin(), bottoms.end(), plate));
        if (loc < (int)bottoms.size()) {
            if (plate > stacks[loc].front()) return false;
            stacks[loc].push_front(plate);
        } else {
            stacks.push_back(qi());
            stacks.back().push_front(plate);
            bottoms.push_back(plate);
        }
        
        while(!stacks.empty() && stacks.front().front() == sorted.front()) {
            stacks.front().pop_front(); sorted.pop_front();
            if (stacks.front().empty()) {
                stacks.pop_front(); bottoms.pop_front();
            }
        }
    }
    return true;
}

int binSearch(int left, int right) {
    int mid = (left + right) / 2;
    if (!poss(mid)) return binSearch(left, mid-1);
    if (poss(mid+1)) return binSearch(mid+1, right);
    return mid;
}

int main() {
    ofstream fout ("dishes.out");
    ifstream fin ("dishes.in");
    
    fin >> N;
    F0R(i, N) fin >> plates[i];
    
    fout << binSearch(1, N) << endl;
    
    return 0;
}
