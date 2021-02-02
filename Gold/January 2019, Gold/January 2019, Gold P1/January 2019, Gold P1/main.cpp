/*
ID: vittal.2
TASK: poetry
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
//#include <algorithm>
#include <list>
#include <map>

using namespace std;

long long MOD = 1000000007;

//fast exponentiation
long long exp(int base, int power){
   if(power == 0) return 1;
   if(power == 1) return base % MOD;
   long long ans = exp(base,power/2);
   ans = ans * ans % MOD;
   if(power%2 == 1) ans = ans*base % MOD;
   return ans % MOD;
}

long long f[5005];
long long g[5005];

map<char, int> rhymeScheme;

int main() {
    ofstream fout ("poetry.out");
    ifstream fin ("poetry.in");
    
    int N, M, K;
    fin >> N >> M >> K;
    
    vector< vector<int> > words(N);
    int x, y;
    for(int i = 0; i < N; i++){
        fin >> x >> y;
        words[y-1].push_back(x);
    }
    
    for(int i = 0; i < M; i++){
        char s;
        fin >> s;
        rhymeScheme[s]++;
    }
    
    f[0] = 1;
    for(int num = 0; num <= K; num++){
        for(int i = 0; i < words.size(); i++){
            for(int j = 0; j < words[i].size(); j++){
                int s = words[i][j];
                if(s + num < K){
                    f[s + num] += f[num];
                    f[s + num] %= MOD;
                }
                if(s + num == K){
                    g[i] += f[num];
                    g[i] %= MOD;
                }
            }
        }
    }
    
    long long prod = 1;
    for(auto rhyme : rhymeScheme){
        long long sum = 0;
        for(int i = 0; i <= N; i++){
            sum += exp(g[i], rhyme.second);
            sum %= MOD;
        }
        prod *= sum;
        prod %= MOD;
    }

    fout << prod << endl;
    return 0;
}
