/*
NAME: Vittal Thirumalai
TASK: exercise
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */

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

const int MAX = 10005, MAXP = 1500;
int N, M;
bool isPrime[MAX];
vi primes;
vector<vi> primePows;
LL dp[MAX][MAXP];

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    for (int p = 2; p*p <= N; p++) {
        if (isPrime[p]) {
            for (int t = p*p; t <= N; t += p) isPrime[t] = false;
        }
    }
    FOR(i, 2, N+1) if (isPrime[i]) primes.pb(i);
}

void sievePowers() {
    primePows.push_back(vector<int> {1});
    for(int prime : primes) {
        vector<int> cur;
        int pow = prime;
        while(pow <= N) {
            cur.push_back(pow);
            pow *= prime;
        }
        primePows.push_back(cur);
    }
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    
    cin >> N >> M;
    sieve();
    sievePowers();
    int pSize = (int)primePows.size();
    
    FOR(i, 1, N+1) dp[i][0] = 1;
    F0R(j, pSize) dp[0][j] = 1;
    
    FOR(i, 1, N+1) {
        FOR(j, 1, pSize) {
            for(LL p : primePows[j]) {
                dp[i][j] = (dp[i][j] + (p <= i ? (LL) p * dp[i-p][j-1] : 0)) % M;
            }
            dp[i][j] = (dp[i][j] + dp[i][j-1]) % M;
        }
    }
//    for (int i : primes) cout << i;
//    for (vi a : primePows) {for (int b : a) cout << b << " "; cout << endl;}
//    FOR(i, 1, N+1) F0R(j, pSize) printf("%d, %d: %lld\n", i, j, dp[i][j]);
    
    cout << dp[N][pSize-1] << endl;
    return 0;
}


