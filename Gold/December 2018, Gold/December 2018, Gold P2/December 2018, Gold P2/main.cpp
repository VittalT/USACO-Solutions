/*
ID: vittal.2
TASK: cowpatibility
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
#include <unordered_map>
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
typedef vector<int> vi;

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = (int)V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int N;
unordered_map<vi, int, VectorHasher> freq;

long C2(int i) {
    return (long) i * (i-1) / 2;
}

int main()
{
    ofstream fout ("cowpatibility.out");
    ifstream fin ("cowpatibility.in");
    
    fin >> N;
    int a[5];
    vi nums;
    F0R(i, N) {
        F0R(j, 5) fin >> a[j];
        sort(a, a+5);
        FOR(b, 1, 32) {
            nums.clear();
            F0R(m, 5) if (b & 1 << m) {
                nums.push_back(a[m]);
            }
            freq[nums]++;
        }
    }

    long sum = C2(N);
    for (auto it = freq.begin(); it != freq.end(); ++it) {
        long n1 = (it->first).size();
        sum += C2(it->second) * ((n1 % 2) ? -1 : 1);
    }
    
    fout << sum;
    return 0;
}
