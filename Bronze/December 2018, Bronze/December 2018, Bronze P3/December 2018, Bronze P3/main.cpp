/*
ID: vittal.2
TASK: measurement
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool sortcol (vector<int> v1, vector<int> v2){
    return v1[0]<v2[0];
}

int main() {
    ofstream fout ("measurement.out");
    ifstream fin ("measurement.in");
    
    int N;
    fin >> N;
    
    vector<int> cowProd{7, 7, 7};
    vector<int> bestCows{0, 1, 2};
    vector<int> newBestCows(0);
    int changes = 0;
    
    vector< vector <int> > data(N, vector<int> (3));
    vector<string> names(N);
    
    for(int i = 0; i < N; i++){
        fin >> data[i][0] >> names[i] >> data[i][2];
    }
    for(int i = 0; i < N; i++){
        if(names[i] == "Bessie"){
            data[i][1] = 0;
        }
        if(names[i] == "Elsie"){
            data[i][1] = 1;
        }
        if(names[i] == "Mildred"){
            data[i][1] = 2;
        }
    }
    
    sort(data.begin(), data.end(), sortcol);
    
    for(int i = 0; i < N; i++){
        cowProd[data[i][1]] += data[i][2];
        for(int i = 0; i < 3; i++){
            if (cowProd[i] == max(max(cowProd[0], cowProd[1]), cowProd[2]))
                newBestCows.push_back(i);
        }
        if(newBestCows != bestCows)
            changes++;
        bestCows = newBestCows;
        newBestCows.clear();
    }
    
    fout << changes;
    
    return 0;
}
