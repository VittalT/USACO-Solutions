/*
ID: vittalt / vittal.2
TASK: photo
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

bool isPermutation (int arr[], int N){
    vector<int> comp(0);
    for(int i = 0; i < N; i++)
        comp.push_back(arr[i]);
    
    sort(comp.begin(), comp.end());
    for(int i = 0; i < N; i++)
        if(comp[i] != i+1)
            return false;
    
    return true;
}

void printArr(int arr[], int N){
    ofstream fout ("photo.out");
    for(int i = 0; i < N-1; i++)
        fout << arr[i] << " ";
    fout << arr[N-1] << endl;
}

int main()
{
    ifstream fin ("photo.in");
    
    int N;
    fin >> N;
    
    int b[N-1];
    for(int i = 0; i < N-1; i++)
        fin >> b[i];
    
    int a[N];
    a[0] = 1;
    for(int i = 1; i < N; i++){
        a[i] = b[i-1] - a[i-1];
    }
    vector<int> even;
    vector<int> odd;
    
    for(int i = 0; i < N; i += 2)
        even.push_back(a[i]);
    for(int i = 1; i < N; i += 2)
        odd.push_back(a[i]);
    
    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end());
    
    if(isPermutation(a, N)){
        printArr(a, N);
    } else {
        int offset1 = 1 - even.front();
        int offset2 = odd.front() - 1;
        int offset = min(offset1, offset2);
        for(int x = 0; x < 2; x++){
            for(int i = 0; i < N; i++){
                if(i % 2 == 0){
                    a[i] += offset;
                } else {
                    a[i] -= offset;
                }
            }
            if(isPermutation(a,N)){
                printArr(a, N);
                return 0;
            } else {
                offset = max(offset1, offset2) - min(offset1, offset2);
            }
        }
    }
    
    
    return 0;
}
