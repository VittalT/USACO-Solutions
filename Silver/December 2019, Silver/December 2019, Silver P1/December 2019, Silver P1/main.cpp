/*
ID: vittal.2
TASK: moobuzz
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
    ofstream fout ("moobuzz.out");
    ifstream fin ("moobuzz.in");
    
    int N;
    fin >> N;
    N--;
    
    vector<int> nums;
    for (int i = 0; i < 15; i++)
        if (i%3 && i%5)
            nums.push_back(i);
    
    int ans = N / nums.size() * 15 + nums[N % nums.size()];
    
    fout << ans << endl;
    return 0;
}
