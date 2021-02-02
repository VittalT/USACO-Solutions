/*
ID: vittal.2
TASK: homework
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool double_equals(double a, double b, double epsilon = 0.00001)
{
    return abs(a - b) < epsilon;
}

int findMinValIndex(int nums[], int length, int minIndex){
    int minValIndex = length-1;
    for(int i = length - 1; i >= minIndex; i--){
        if(nums[i] < nums[minValIndex])
            minValIndex = i;
    }
    
    return minValIndex;
}

int main() {
    ofstream fout ("homework.out");
    ifstream fin ("homework.in");
    
    vector<int> allK(0);
    
    int N;
    fin >> N;
    
    int nums[N];
    for(int i = 0; i < N; i++){
        fin >> nums[i];
    }
    
    double avgs[N];
    avgs[N-1] = nums[N-1];
    for(int i = 1; i < N; i++){
        avgs[N-1-i] = avgs[N-i]+nums[N-1-i];
    }
    
    int currentSet = 1;
    int minValIndex;
    
    while(currentSet < N){
        minValIndex = findMinValIndex(nums, N, currentSet);
        for(int i = currentSet; i <= minValIndex; i++){
            if(currentSet <= N-2)
                avgs[i] = (avgs[i] - nums[minValIndex]) / (N-1-i);
        }
        currentSet = minValIndex+1;
    }
    
    int maxValIndex = 1;
    for(int i = 1; i <= N-2; i++){
        if(double_equals(avgs[i], avgs[maxValIndex])){
            allK.push_back(i);
        } else if(avgs[i] > avgs[maxValIndex]) {
            maxValIndex = i;
            allK.clear();
            allK.push_back(i);
        }
    }
    
    for(int i = 0; i < allK.size(); i++){
        fout << allK.at(i) << endl;
    }

    
    return 0;
}
