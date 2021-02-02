/*
NAME: Vittal Thirumalai
TASK: threesum
LANG: C++11
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
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef deque<int> qi;
typedef long long LL;

int N, Q;
LL dp[5005][5005];
int A[5005];
vector<int> indices;
//unordered_map<int, int> freq;

//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
//gp_hash_table<int, int> freq;

const int MAX_RANGE = 1e6;
int freq[2*MAX_RANGE + 1];

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    
    cin >> N >> Q;
    FOR(i, 1, N+1) {
        cin >> A[i];
    }
    
    FOR(i, 1, N+1) {
        //freq.clear()
        //gp_hash_table<int, int> freq({},{},{},{},{1<<13});
        FOR(k, i+1, N+1) {
            int idx = MAX_RANGE-A[i]-A[k];
            if (0 <= idx && idx <= 2*MAX_RANGE) dp[i][k] += freq[idx];
            freq[MAX_RANGE + A[k]]++;
        }
        FOR(k, i+1, N+1) freq[MAX_RANGE + A[k]]--;
    }

    FOR(i, 1, N+1) FOR(j, 1, N+1) {
        dp[i][j] += (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
    }

    int l, r;
    F0R(i, Q) {
        cin >> l >> r;
        cout << dp[r][r] - dp[r][l-1] - dp[l-1][r] + dp[l-1][l-1] << endl;
    }
    return 0;
}

/*
int N, Q;
LL dp[5005][5005];
pi A[5005];
vector<int> indices;
 
int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    
    cin >> N >> Q;
    int a;
    FOR(i, 1, N+1) {
        cin >> a;
        A[i] = {a, i};
    }
    sort(A+1, A+N+1);
    
    FOR(i, 1, N+1) {
        int j = i+1, k = N, sum;
        while (j < k) {
            sum = A[i].f + A[j].f + A[k].f;
            if (sum < 0) ++j;
            else if (sum > 0) --k;
            else {
                if (A[j].f == A[k].f) {
                    FOR(j_i, j, k+1) FOR(k_i, j_i+1, k+1) {
                        indices = {A[i].s, A[j_i].s, A[k_i].s};
                        dp[*min_element(indices.begin(), indices.end())][*max_element(indices.begin(), indices.end())]++;
                    }
                    break;
                } else {
                    int j_2 = j+1, k_2 = k-1;
                    while (A[j_2].f == A[j].f) ++j_2;
                    while (A[k_2].f == A[k].f) --k_2;
                    FOR(j_i, j, j_2) FOR(k_i, k_2+1, k+1) {
                        indices = {A[i].s, A[j_i].s, A[k_i].s};
                        dp[*min_element(indices.begin(), indices.end())][*max_element(indices.begin(), indices.end())]++;
                    }
                    j = j_2; k = k_2;
                }
            }
        }
    }

    FOR(i, 1, N+1) FOR(j, 1, N+1) {
        dp[i][j] += (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
    }

    int l, r;
    F0R(i, Q) {
        cin >> l >> r;
        cout << dp[r][r] - dp[r][l-1] - dp[l-1][r] + dp[l-1][l-1] << endl;
    }
    return 0;
}
*/
