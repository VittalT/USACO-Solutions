/*
ID: vittal.2
TASK: perimeter
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <algorithm>
//#include <list>

using namespace std;

struct Point{
    int x, y;
};

int MAX = 10000;
int per = 0;
vector<Point> points(0);
bool coveredPoints[1000][1000];

void updatePerimeter(string mat[], Point p, int N){
    int numAdj = 0;
    if(p.y < N-1 && coveredPoints[p.x][p.y+1])
        numAdj++;
    if(p.y > 0 && coveredPoints[p.x][p.y-1])
        numAdj++;
    if(p.x < N-1 && coveredPoints[p.x+1][p.y])
        numAdj++;
    if(p.x > 0 && coveredPoints[p.x-1][p.y])
        numAdj++;
    
    if(numAdj == 0)
        per = 4;
    else if(numAdj == 1)
        per += 2;
    else if(numAdj == 3)
        per -= 2;
    else if(numAdj == 4)
        per -= 4;
}

void floodFill(string mat[], Point p, int N){
    if(p.x < 0 || p.x >= N || p.y < 0 || p.y >= N || coveredPoints[p.x][p.y] || mat[p.x][p.y] != '#')
        return;
    
    points.push_back(p);
    coveredPoints[p.x][p.y]=true;
    
    updatePerimeter(mat, p, N);
    
    floodFill(mat, {p.x, p.y+1}, N);
    floodFill(mat, {p.x, p.y-1}, N);
    floodFill(mat, {p.x+1, p.y}, N);
    floodFill(mat, {p.x-1, p.y}, N);
}

int main() {
    ofstream fout ("perimeter.out");
    ifstream fin ("perimeter.in");
    
    int N;
    fin >> N;
    string mat[N];
    for(int i = 0; i < N; i++){
        fin >> mat[i];
    }

    int area = 0;
    int maxArea = 0;
    int minPer = MAX;
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(mat[i][j] == '#' && !coveredPoints[i][j]){
                points.clear();
                floodFill(mat, {i,j}, N);
                area = (int)points.size();
                if(area > maxArea){
                    maxArea = area;
                    minPer = per;
                }
                if(area == maxArea && per < minPer)
                    minPer = per;
            }

    fout << maxArea << " " << minPer << endl;
    return 0;
}
