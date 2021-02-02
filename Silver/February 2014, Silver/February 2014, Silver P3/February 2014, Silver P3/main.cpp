/*
ID: vittal.2
TASK: scode
LANG: C++11
*/
/* LANG can be C++11 or C++14 for those more recent releases */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;

struct Input {
    string sCode;
    int val;
    
    Input(string ss, int ii){
        sCode = ss;
        val = ii;
    }
};

vector <vector <Input> > allWays(101);

int numOfWays(string subs, string s){
    int num = 0;
    
    if(s.substr(0,subs.size()).compare(subs) == 0){
        num++;
    }
    if(s.substr(s.size()-subs.size()).compare(subs) == 0){
        num++;
    }
    
    return num;
}

int v_find(string s){
    vector<Input> ways = allWays[s.size()];
    for(int i = 0; i < ways.size(); i++){
        if(ways[i].sCode.compare(s) == 0)
            return ways[i].val;
    }
    return -1;
}

void numTotalWays(string code){
    string s1, s2, subs;
    int numWays = 0;
    int totalWays = 0;
    
    for(int i = 1; i < code.size(); i++){
        if (code.size() == 2){
            break;
        }
        s1 = code.substr(0,i);
        s2 = code.substr(i);
        if(s1.size() < s2.size()){
            numWays = numOfWays(s1, s2);
            if(numWays != 0)
                totalWays += numWays * (v_find(s2) + 1);
        }
        if(s1.size() > s2.size()){
            numWays = numOfWays(s2, s1);
            if(numWays != 0)
                totalWays += numWays * (v_find(s1) + 1);
        }
    }
    
    allWays[code.size()].push_back(Input (code, totalWays % 2014));
}

int main() {
    ifstream fin ("scode.in");
    ofstream fout ("scode.out");

    string fullCode;
    fin >> fullCode;
    
    for(int i = 2; i <= fullCode.size(); i ++){
        for(int j = 0; j <= fullCode.size() - i; j++){
            numTotalWays(fullCode.substr(j, i));
        }
    }
        
    fout << allWays[fullCode.size()][0].val;
    
    return 0;
}


/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;

struct Input {
    string sCode;
    int val;
    
    Input(string ss, int ii){
        sCode = ss;
        val = ii;
    }
};

vector<Input> known(0);

bool comp(Input i1, Input i2){
    return i1.sCode < i2.sCode;
}

int numOfWays(string subs, string s){
    int num = 0;
    
    if(s.substr(0,subs.size()).compare(subs) == 0){
        num++;
    }
    if(s.substr(s.size()-subs.size()).compare(subs) == 0){
        num++;
    }
    
    return num;
}

int numTotalWays(string code){
    string s1, s2, subs;
    int numWays = 0;
    int totalWays = 0;
    int index = 0;
    
    for(int i = 1; i < code.size(); i++){
        s1 = code.substr(0,i);
        s2 = code.substr(i);
        if(s1.size() < s2.size()){
            numWays = numOfWays(s1, s2);
            if(numWays != 0){
                index = find(known.sCode == s2);
                struct =
                if(index != known.size()){
                    totalWays += numWays * (known[index].val + 1);
                } else{
                    totalWays += numWays * (numTotalWays(s2) + 1);
                }
            }
        }
        if(s1.size() > s2.size()){
            numWays = numOfWays(s2, s1);
            if(numWays != 0){
                //index = distance(known.begin(), find(known.begin(), known.end(), s1));
                if(index != known.size()){
                    totalWays += numWays * (known[index].val + 1);
                } else {
                    totalWays += numWays * (numTotalWays(s1) + 1);
                }
            }
        }
    }
    
    Input in = Input (code, totalWays % 2014);
    known.insert(lower_bound(known.begin(), known.end(), in, comp), in);
    return totalWays % 2014;
}

int main() {
    ifstream fin ("scode.in");
    ofstream fout ("scode.out");

    string code;
    cin >> code;
    cout << numTotalWays(code);
    
    return 0;
}
*/


/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits.h>

using namespace std;

int numOfWays(string subs, string s){
    int num = 0;
    
    if(s.substr(0,subs.size()).compare(subs) == 0){
        num++;
    }
    if(s.substr(s.size()-subs.size()).compare(subs) == 0){
        num++;
    }
    
    return num;
}

int numTotalWays(string code){
    string s1, s2, subs;
    int numWays = 0;
    int totalWays = 0;
    
    for(int i = 1; i < code.size(); i++){
        s1 = code.substr(0,i);
        s2 = code.substr(i);
        if(s1.size() < s2.size()){
            numWays = numOfWays(s1, s2);
            if(numWays != 0)
                totalWays += numWays * (numTotalWays(s2) + 1);
        }
        if(s1.size() > s2.size()){
            numWays = numOfWays(s2, s1);
            if(numWays != 0)
                totalWays += numWays * (numTotalWays(s1) + 1);
        }
    }
    
    return totalWays % 2014;
}

int main() {
    ifstream fin ("scode.in");
    ofstream fout ("scode.out");

    string code;
    fin >> code;
    
    fout << numTotalWays(code);
    
    return 0;
}

*/
