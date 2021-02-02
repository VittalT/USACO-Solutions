#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define FORLL(i,a,b) for (long long i = (a); i < (b); ++i)
#define F0RLL(i,a) FORLL(i,0,a)
#define f first
#define s second
typedef long long LL;
typedef pair<int, int> pi;

LL N, K, M;
const int MAXN = 1e5 + 5;
const int MAXK = 2e5 + 5;
int cow_at[MAXN], num_poss[MAXN];
pi swaps[MAXK];
vector<int> poss_pos[MAXN], poss_pos_round[MAXN];
int cur_poss[MAXN];
bool visited_cow[MAXN];
int num;

void addAll(int cow, bool isFull) {
    if (isFull) {
        for (int pos : poss_pos_round[cow]) {
            cur_poss[pos]++;
            if (cur_poss[pos] == 1) num++;
        }
    } else {
        for (int pos : poss_pos[cow]) {
            cur_poss[pos]++;
            if (cur_poss[pos] == 1) num++;
        }
    }
}

void removeAll(int cow, bool isFull) {
    if (isFull) {
        for (int pos : poss_pos_round[cow]) {
            cur_poss[pos]--;
            if (cur_poss[pos] == 0) num--;
        }
    } else {
        for (int pos : poss_pos[cow]) {
            cur_poss[pos]--;
            if (cur_poss[pos] == 0) num--;
        }
    }
}

int main() {
    
    cin >> N >> K >> M;
    int a, b;
    F0R(i, K) {
        cin >> a >> b;
        swaps[i] = {a,b};
    }
    int temp;
    if (M != (LL) 1e18) {
        FOR(i, 1, N+1) {
            cow_at[i] = i;
            poss_pos[cow_at[i]].push_back(i);
        }
    
        F0R(i, M % K) {
            temp = cow_at[swaps[i].f];
            cow_at[swaps[i].f] = cow_at[swaps[i].s];
            cow_at[swaps[i].s] = temp;
            poss_pos[cow_at[swaps[i].f]].push_back(swaps[i].f);
            poss_pos[cow_at[swaps[i].s]].push_back(swaps[i].s);
        }
    }
    
    FOR(i, 1, N+1) {
        cow_at[i] = i;
        poss_pos_round[cow_at[i]].push_back(i);
    }
    
    F0R(i, K) {
        temp = cow_at[swaps[i].f];
        cow_at[swaps[i].f] = cow_at[swaps[i].s];
        cow_at[swaps[i].s] = temp;
        poss_pos_round[cow_at[swaps[i].f]].push_back(swaps[i].f);
        poss_pos_round[cow_at[swaps[i].s]].push_back(swaps[i].s);
    }
    
    FOR(i, 1, N+1) if (!visited_cow[i]) {
        memset(cur_poss, 0, sizeof(cur_poss)); num = 0;
        int cur_cow = i; bool wraps = false;
        visited_cow[cur_cow] = true;
        addAll(cur_cow, false);
        F0RLL(i, M / K) {
            cur_cow = cow_at[cur_cow];
            visited_cow[cur_cow] = true;
            addAll(cur_cow, true);
            if (cur_cow == i) {
                wraps = true; break;
            }
        }
        
        if (wraps) {
            cur_cow = i;
            do {
                num_poss[cur_cow] = num;
                cur_cow = cow_at[cur_cow];
            } while (cur_cow != i);
        } else {
            int first_head = cur_cow;
            int tail = i;
            do {
                removeAll(tail, false);
                tail = cow_at[tail]; removeAll(tail, true); addAll(tail, false);
                cur_cow = cow_at[cur_cow];
                visited_cow[cur_cow] = true;
                addAll(cur_cow, true);
                num_poss[cur_cow] = num;
            } while(cur_cow != first_head);
        }
    }
    
    FOR(i, 1, N+1) {
        cout << num_poss[i] << endl;
    }
    return 0;
}
