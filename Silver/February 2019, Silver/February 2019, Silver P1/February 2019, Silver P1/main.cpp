/*
ID: vittalt
TASK: herding
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <queue>

using namespace std;

int main()
{
    ofstream fout ("herding.out");
    ifstream fin ("herding.in");
    
    int N;
    fin >>  N;
    int cowPos[N];
    
    for(int i = 0; i < N; i++){
        fin >> cowPos[i];
        cowPos[i]--;
    }
    
    sort(cowPos, cowPos+N);
    
    deque<int> currCows(0);
    for(int i = 0; cowPos[i] < N; i++){
        currCows.push_back(i);
    }
    
    int currStartIndex = 0;
    
    if((int)currCows.size() == 0){
        currCows.push_back(0);
        currStartIndex = cowPos[0] - N + 1;
    }
    
    bool cut = false;
    
    if(cowPos[N-1]-cowPos[0] == N-1){
        fout << 0 << endl;
        cut = true;
    } else if(cowPos[N-2]-cowPos[0] == N-2 || cowPos[N-1]-cowPos[1] == N-2){
        if(cowPos[N-1]-cowPos[0] == N)
            fout << 1 << endl;
        else
            fout << 2 << endl;
        cut = true;
    }
    
    int maxInN = (int)currCows.size();
    
    int front, back;
    int lastPopped = -1;
    while(currCows.back() != N - 1){
        front = cowPos[currCows.front()] - currStartIndex + 1;
        back = cowPos[currCows.back()+1] - (currStartIndex + N - 1);
        if(front >= back){
            currStartIndex += back;
            currCows.push_back(currCows.back()+1);
        }
        if(front <= back){
            currStartIndex += front;
            lastPopped = currCows.front();
            currCows.pop_front();
        }
        if(front == back){
            currStartIndex -= front;
        }
        
        maxInN = max(maxInN, (int)currCows.size());
        
        if(currCows.size() == 0){
            currCows.push_back(lastPopped+1);
            currStartIndex = cowPos[lastPopped+1] - N + 1;
        }
        
    }
    
    if(!cut)
        fout << N - maxInN << endl;
    
    int maxDistance = max(cowPos[N-2] - cowPos[0], cowPos[N-1] - cowPos[1]);
    
    fout << maxDistance - N + 2 << endl;
    
    return 0;
}

