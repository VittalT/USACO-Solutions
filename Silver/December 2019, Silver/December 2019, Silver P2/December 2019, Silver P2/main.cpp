/*
ID: vittal.2
TASK: meetings
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

using namespace std;

struct Cow{
    int w;
    int x;
    int d;
};

bool comp(Cow c1, Cow c2){
    if (c1.x == c2.x)
        return c1.d < c2.d;
    return c1.x < c2.x;
}

vector <Cow> cows;
vector <Cow> cows_dir[2];

int num_meetings(vector<Cow> cows){
    int num_right = 0, num_meetings = 0;
    
    for (Cow cow : cows)
        (cow.d == 1) ? num_right += 1 : num_meetings += num_right;
    
    return num_meetings;
    
}

int main()
{
    ofstream fout ("meetings.out");
    ifstream fin ("meetings.in");

    int N, L;
    fin >> N >> L;
    int w, x, d;
    int total_weight = 0, total_left = 0;
    for (int i = 0; i < N; i++) {
        fin >> w >> x >> d;
        Cow cow = {w, x, d};
        cows.push_back(cow);
        total_weight += w;
        if (d == -1) total_left += 1;
        (d == 1) ? cows_dir[1].push_back(cow) : cows_dir[0].push_back(cow);
    }
    
    sort(cows.begin(), cows.end(), comp);
    for (int dir = 0; dir < 2; ++dir)
        sort(cows_dir[dir].begin(), cows_dir[dir].end(), comp);
    
    int total_meetings = num_meetings(cows);
    
    int cur_weight = 0, cur_time = 0, left = 0, right = 0;
    while (cur_weight < (total_weight+1) / 2){
        int left_time = (left < cows_dir[0].size()) ? cows_dir[0][left].x : INT_MAX;
        int right_time = (right < cows_dir[1].size()) ? L - cows_dir[1][cows_dir[1].size()-1 - right].x : INT_MAX;
        cur_weight += (left_time < right_time) ? cows[left].w : cows[N-1-right].w;
        cur_time = min(left_time, right_time);
        (left_time < right_time) ? ++left : ++right;
    }
    
    for (Cow& cow : cows)
        cow.x = cow.x + cur_time * cow.d;
    
    sort(cows.begin(), cows.end(), comp);
    int remaining_meetings = num_meetings(cows);
    
    fout << total_meetings - remaining_meetings << endl;
    return 0;
}

/*
95 577341897
1 103271811 -1
1 243784241 -1
1 476574632 -1
1 401074163 1
1 354873788 1
1 197679134 1
1 124691977 -1
1 484640858 -1
1 82493224 1
1 523835371 -1
1 409118122 1
1 160176326 -1
1 136697193 1
1 393892687 -1
1 511387040 -1
1 533947735 1
1 83909253 1
1 63883156 -1
1 104115643 -1
1 283106146 -1
1 325785183 1
1 1747163 1
1 478199039 1
1 457828194 -1
1 512475346 1
1 137128431 -1
1 379461746 1
1 529373261 -1
1 223260298 1
1 178505982 -1
1 134337944 1
1 381313859 -1
1 202125165 -1
1 502396440 1
1 55969434 1
1 44918277 1
1 394731093 1
1 241300710 1
1 401609230 1
1 330699937 1
1 169193334 1
1 101164679 1
1 404785993 -1
1 238055821 -1
1 548288756 1
1 531780946 1
1 69429143 -1
1 51417221 -1
1 500996908 1
1 338649334 1
1 187804952 -1
1 62654041 -1
1 142349339 1
1 413382299 -1
1 101062408 -1
1 26192051 -1
1 72868673 -1
1 313176780 1
1 238112448 -1
1 130815877 -1
1 45043453 1
1 235305405 -1
1 574649649 1
1 514032274 -1
1 314972371 -1
1 274958045 1
1 34191900 1
1 147539044 -1
1 258460937 1
1 71232117 1
1 342140261 1
1 60819487 1
1 173981970 1
1 192400570 -1
1 422257323 1
1 522285966 -1
1 305804067 -1
1 347462531 -1
1 255335851 -1
1 175206791 -1
1 490921109 -1
1 436840551 -1
1 373022404 -1
1 214628327 -1
1 197208017 -1
1 254026322 1
1 486398112 1
1 565492308 1
1 287532215 -1
1 117837967 1
1 29346844 -1
1 37551409 1
1 187834941 -1
1 184270046 -1
1 274961734 -1
*/
