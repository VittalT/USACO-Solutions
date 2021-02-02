/*
ID: vittal.2
TASK: mountains
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <list>

using namespace std;

struct Point {
    int x, y;
};

bool diffXCord(Point p1, Point p2){
    if ((p1.y - p1.x) == (p2.y - p2.x))
        return (p1.x + p1.y) > (p2.x + p2.y);
    return (p1.y - p1.x) > (p2.y - p2.x);
}

int findMaxDiffIndex(vector<Point> points){
    int index = 0;
    int max = 0;
    for(int i = 0; i < points.size(); i++){
        if(max < (points[i].x + points[i].y)){
            max = points[i].x + points[i].y;
            index = i;
        }
    }
    
    return index;
}

int main() {
    ofstream fout ("mountains.out");
    ifstream fin ("mountains.in");
    
    int N;
    fin >> N;
    
    vector<Point> points;
    int x, y;
    for(int i = 0; i < N; i++){
        fin >> x >> y;
        points.push_back({x,y});
    }
    
    sort(points.begin(), points.end(), diffXCord);
    
    int numMountains = 0;
    int index;
    while(points.size() != 0){
        index = findMaxDiffIndex(points);
        numMountains++;
        points.erase(points.begin() + index, points.end());
    }
    
    fout << numMountains << endl;
    return 0;
}
