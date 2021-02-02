/*
ID: vittalt / vittal.2
TASK: word
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
    ofstream fout ("word.out");
    ifstream fin ("word.in");
    
    int N, K;
    fin >> N >> K;
    deque<string> words(N);
    
    for(int i = 0; i < N; i++)
        fin >> words[i];
    
    int length = 0;
    while(words.size() != 0){
        if(words.front().size() > K){
            fout << endl << words.front() << endl;
            words.pop_front();
            break;
        } else {
            fout << words.front();
            length += words.front().size();
            words.pop_front();
        }
        while(words.size() != 0){
            if(length + words.front().size() <= K){
                fout << " " << words.front();
                length += words.front().size();
                words.pop_front();
            } else {
                fout << endl;
                length = 0;
                break;
            }
        }
        length = 0;
    }
    
    return 0;
}

