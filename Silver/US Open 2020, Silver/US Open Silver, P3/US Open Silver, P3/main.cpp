/*
ID: vittalt
TASK: moop
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

struct point {
    int x;
    int y;
};

bool compX(point p1, point p2){
    if(p1.x == p2.x)
        return p1.y < p2.y;
    return p1.x < p2.x;
}

bool compY(point p1, point p2){
    if(p1.y == p2.y)
        return p1.x < p2.x;
    return p1.y < p2.y;
}

bool operator== (point p1, point p2){
    return p1.x == p2.x && p1.y == p2.y;
}

int N;
vector<point> points;

int main()
{
    ofstream fout ("moop.out");
    ifstream fin ("moop.in");

    fin >> N;
    int a, b;
    F0R(i, N){
        fin >> a >> b;
        points.push_back({a,b});
    }
    sort(points.begin(), points.end(), compX);
    
    int minL[N], maxR[N];
    minL[0] = points[0].y; maxR[N-1] = points[N-1].y;
    FOR(i, 1, N) minL[i] = min(minL[i-1], points[i].y);
    ROF(i, 0, N-1) maxR[i] = max(maxR[i+1], points[i].y);
    
    int ans = 1;
    F0R(i, N-1) if (minL[i] > maxR[i+1]) ans++;
    
    fout << ans;
    
}


//int main()
//{
//    ofstream fout ("moop.out");
//    ifstream fin ("moop.in");
//
//    fin >> N;
//    int a, b;
//    for(int i = 0; i < N; i++){
//        fin >> a >> b;
//        spinsX.push_back({a,b});
//        spinsY.push_back({a,b});
//    }
//    sort(spinsX.begin(), spinsX.end(), compX);
//    sort(spinsY.begin(), spinsY.end(), compY);
//
//    int ans = 0;
//    point curr, max;
//    int Yindex;
//    for(int i = 0; i < N; i++){
//        curr = spinsX[i];
//        Yindex = (int)distance(spinsY.begin(), lower_bound(spinsY.begin(), spinsY.end(), curr, compY));
//        if(Yindex != spinsY.size() && spinsY[Yindex] == curr){
//            if(spinsY.back() == curr){
//                spinsY.pop_back();
//                ans++;
//            } else {
//                max = curr;
//                for(int j = Yindex; j < spinsY.size(); j++)
//                    if(spinsY[j].x > max.x || (spinsY[j].x == max.x && spinsY[j].y > max.y))
//                        max = spinsY[j];
//                spinsY.erase(spinsY.begin() + Yindex, spinsY.end());
//                spinsY.push_back(max);
//            }
//        }
//    }
//
//    fout << ans;
//
//}
