/*
ID: vittal.2
TASK: teamwork
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
#include <tuple>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
typedef pair<int, int> pi;

int N, K;
int skills[10005], prf[10005], dp[10005];

int main()
{
    ofstream fout ("teamwork.out");
    ifstream fin ("teamwork.in");
    
    fin >> N >> K;
    F0R(i, N) fin >> skills[i];
    
    dp[0] = 0;
    
    FOR(i, 1, N+1) {
        int val = 0, max_skill = 0, total_skill;
        FOR(j, 1, K+1) if (j <= i) {
            max_skill = max(max_skill, skills[i-j]);
            total_skill = max_skill * j;
            val = max(val, dp[i-j] + total_skill);
        }
        dp[i] = val;
    }
    
    fout << dp[N];
    return 0;
}
