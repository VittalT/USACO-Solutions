/*
ID: vittalt
TASK: cereal
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

struct likes {
    int like1;
    int like2;
};

int N, M, num;
vector<int> ordering [100000];
likes cows[100000];
int pos1[100000];
int pos2[100000];
bool isTaken[100000];
int currCereal[100000];

int main()
{
    ofstream fout ("cereal.out");
    ifstream fin ("cereal.in");
    
    fin >> N >> M;
    int a, b;
    for(int i = 0; i < N; i++){
        fin >> a >> b;
        a--;
        b--;
        pos1[i] = (int)ordering[a].size();
        ordering[a].push_back(i);
        pos2[i] = (int)ordering[b].size();
        ordering[b].push_back(i);
        cows[i] = {a,b};
        
        if(!isTaken[a]){
            isTaken[a] = true;
            num++;
            currCereal[i]  = 1;
        } else if (!isTaken[b]){
            isTaken[b] = true;
            num++;
            currCereal[i] = 2;
        }
    }
    
    fout << num << endl;
    
    int open, cow, index;
    for(int i = 0; i < N-1; i++){
        open = cows[i].like1;
        index = pos1[i] + 1;
        num--;
        while(index < ordering[open].size()){
            cow = ordering[open][index];
            if(currCereal[cow] == 0){
                if(open == cows[cow].like1)
                    currCereal[cow] = 1;
                else currCereal[cow] = 2;
                num++;
                break;
            } else if (currCereal[cow] == 2){
                currCereal[cow] = 1;
                open = cows[cow].like2;
                index = pos2[cow] + 1;
            } else index++;
        }
        
        fout << num << endl;
    }
    
}
