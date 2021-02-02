/*
ID: vittal.2
TASK: convention2
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

struct Cow {
    int a;
    int t;
    int s;
};

struct Seniority {
public:
    bool operator()(Cow c1,Cow c2) {
        return c1.s > c2.s;
    }
};


bool arrivalTime (Cow c1, Cow c2) {
    if (c1.a == c2.a) return c1.s < c2.s;
    return c1.a < c2.a;
}

int N;
deque <Cow> cows;

int main()
{
    ofstream fout ("convention2.out");
    ifstream fin ("convention2.in");
    
    fin >> N;
    int a, t;
    F0R (i, N) {
        fin >> a >> t;
        cows.push_back({a,t,i});
    }
    sort(cows.begin(), cows.end(), arrivalTime);
    
    priority_queue <Cow, vector<Cow>, Seniority> waitlist;
    
    int max_time = 0, cur_time = 0;
    Cow grazing = cows.front(); cows.pop_front();
    while (!cows.empty() || !waitlist.empty()) {
        cur_time = max(cur_time, grazing.a) + grazing.t;
        while (!cows.empty() && (cows[0].a <= cur_time || waitlist.empty())) {
            waitlist.push(cows[0]); cows.pop_front();
        }
        grazing = waitlist.top(); waitlist.pop();
        max_time = max(max_time, cur_time - grazing.a);
    }
    
    fout << max_time << endl;
    return 0;
}
