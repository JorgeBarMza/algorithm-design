#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;

vector<vector<string>> memo; //100 char limit


//string recursiveLCS(string w1, string w2){
//    //memo.assign(100,vector<string>(100,"-1"));
//    if(memo[w1.size()][w2.size()] == "-1"){
//        if(w1.size() == 0 || w2.size() == 0) return "";
//        if(w1[w1.size()-1] == w2[w2.size()-1]) {
//            memo[w1.size()][w2.size()] = w1[w1.size()-1]+ LCS(w1.erase(w1.size()-1, 1), w2.erase(w2.size()-1,1));
//        }
//        else {
//            string temp1 = w1;
//            string temp2 = w2;
//            temp1.erase(temp1.size()-1,1);
//            temp2.erase(temp2.size()-1,1);
//            string str1 = LCS(temp1, w2);
//            string str2 = LCS(w1,temp2);
//            if(str1.size() >= str2.size()) memo[w1.size()][w2.size()] = str1;
//            memo[w1.size()][w2.size()] = str2;
//        }
//    }
//    return memo[w1.size()][w2.size()];
//}

bool w1ShorterThanW2(string w1, string w2) {
    return (w1.size() <= w2.size());
}

string bottomUpLCS(string w1, string w2){
    int dpTable[w1.size()+1][w2.size()+1];
    for (int i = 0; i <= w1.size() ; ++i) {
        for (int j = 0; j <= w2.size() ; ++j) {
            if(i == 0 || j == 0)
                dpTable[i][j] = 0;
            else if(w1[i-1] == w2[j-1]){
                dpTable[i][j] = 1 + dpTable[i-1][j-1];
            }
            else
                dpTable[i][j] = max(dpTable[i-1][j], dpTable[i][j-1]);
        }
    }

    string res = "";

    int row = w1.size();
    int col = w2.size();
    while(row > 0 && col > 0){
        if(w1[row-1] == w2[col-1]){
            res += w1[row-1];
            row--; col--;
        }
        else
            if(dpTable[row-1][col] > dpTable[row][col-1])
                row--;
            else
                col--;
    }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    time_t t1 = clock();
//    memo.assign(100,vector<string>(100,"-1"));
    cout << bottomUpLCS("ddddddddddddddddddddddb", "bcccccccccccccccccccccccc");
    cout << "\n";
    cout << clock() - t1;
}