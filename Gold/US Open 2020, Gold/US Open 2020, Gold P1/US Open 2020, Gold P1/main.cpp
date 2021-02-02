/*
NAME: Vittal Thirumalai
TASK: haircut
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

const int MAX = 1e5 + 5;
int N;
LL A[MAX], fk[MAX], freq[MAX];

void inc(LL i) {
    for(++i; i <= N; i += i&-i) {
        fk[i]++;
    }
}

LL getSum(LL i) {
    LL sum = 0;
    for(++i; i > 0; i -= i&-i) {
        sum += fk[i];
    }
    return sum;
}

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    
    cin >> N;
    F0R(i, N) cin >> A[i];
    
    FOR(i, 1, N) {
        inc(A[i-1]);
        freq[A[i]] += i - getSum(A[i]);
    }
    
    FOR(i, 1, N+1) freq[i] += freq[i-1];
    
    cout << 0 << endl;
    F0R(i, N-1) cout << freq[i] << endl;
    
    return 0;
}

