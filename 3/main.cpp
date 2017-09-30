#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> memo; //100 char limit

string LCS(string w1, string w2){
    memo.assign(100,vector<string>(100,"-1"));
    if(memo[w1.size()][w2.size()] == "-1"){
        if(w1.size() == 0 || w2.size() == 0) return "";
        if(w1[w1.size()-1] == w2[w2.size()-1]) {
            memo[w1.size()][w2.size()] = w1[w1.size()-1]+ LCS(w1.erase(w1.size()-1, 1), w2.erase(w2.size()-1,1));
        }
        else {
            string temp1 = w1;
            string temp2 = w2;
            temp1.erase(temp1.size()-1,1);
            temp2.erase(temp2.size()-1,1);
            string str1 = LCS(temp1, w2);
            string str2 = LCS(w1,temp2);
            if(str1.size() >= str2.size()) memo[w1.size()][w2.size()] = str1;
            memo[w1.size()][w2.size()] = str2;
        }
    }
    return memo[w1.size()][w2.size()];
}
int main() {
    memo.assign(100,vector<string>(100,"-1"));
    cout << LCS("abcde", "cdefg");
}