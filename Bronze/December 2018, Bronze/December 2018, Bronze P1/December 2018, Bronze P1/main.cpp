/*
ID: vittal.2
TASK: billboard
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int overlapArea(int rect1[4], int rect2[4]){
    int x = 0;
    int y = 0;
    
    int xArr[] = {rect1[0], rect1[2], rect2[0], rect2[2]};
    if (rect1[2] <= rect2[0] || rect2[2] <= rect1[0])
        return 0;
    sort(xArr, xArr+4);
    x = xArr[2] - xArr[1];
    
    int yArr[] = {rect1[1], rect1[3], rect2[1], rect2[3]};
    if (rect1[3] <= rect2[1] || rect2[3] <= rect1[1])
        return 0;
    sort(yArr, yArr+4);
    y = yArr[2] - yArr[1];
    
    return x*y;
}

int area(int rect[4]){
    return abs((rect[3] - rect[1])*(rect[2]-rect[0]));
}

int main() {
    ofstream fout ("billboard.out");
    ifstream fin ("billboard.in");
    
    int rect1[4];
    int rect2[4];
    int rect3[4];
    
    for(int i = 0; i < 4; i++){
        fin >> rect1[i];
    }
    for(int i = 0; i < 4; i++){
        fin >> rect2[i];
    }
    for(int i = 0; i < 4; i++){
        fin >> rect3[i];
    }
    
    fout << area(rect1) - overlapArea(rect1, rect3) + area(rect2) - overlapArea(rect2, rect3);
    return 0;
}
