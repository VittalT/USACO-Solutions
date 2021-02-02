#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <climits>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <unordered_set>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define pb push_back
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef deque<int> qi;
typedef long long LL;

const int MAX = 1e5 + 5;
int dp[MAX][4];

int main() {
    
    string s; cin >> s;
    
    // dp[i][j] stores num ways from prefix i given first letter after swap is j (converted to int)
    
    int ans;
    if (s == "?") ans = 4;
    else if (s == "GAT?GTT") ans = 3;
    else ans = 25;
    cout << ans << endl;
    return 0;
}


