#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;
int dp[100]; //100 words max

int calcBadness(vector<string>& words, int firstW, int lastW, int lineLenght, int optimalSpaceLength){
    int remainingLength = lineLenght, individualSpaceLength = 1;
    int wordCount = lastW-firstW+1;
    for (int i = firstW; i <= lastW ; ++i) {
        remainingLength -= (words[i].size() + 1);
    }
    remainingLength++; //last word of line has no space
    if(0 <= remainingLength && lastW == words.size()-1)
        return 0;
    if(wordCount == 1){
        individualSpaceLength = remainingLength;
        lastW++; // to avoid returning 0
    }
    else{
        if(remainingLength % (wordCount-1) != 0 || remainingLength < 0)
            return INT32_MAX; // don't fit
        while(remainingLength != 0){
            individualSpaceLength += 1;
            remainingLength -= (wordCount-1);
        }
    }
    return (lastW-firstW) * abs(individualSpaceLength - optimalSpaceLength);
}

int makeLines(vector<string> words,  int index, int lineLength, int optimalSpaceLength) {
    if(index == words.size())
        return 0;
    if(dp[index] != -1)
        return dp[index];
    int minBadness = INT32_MAX, nextWord;
    for (int i = index; i < words.size(); ++i) {
        int badness = calcBadness(words, index, i, lineLength, optimalSpaceLength);
        if(badness <= minBadness){
            minBadness = badness;
            nextWord = i+1;
        }
    }
    return dp[index] = minBadness + makeLines(words, nextWord, lineLength, optimalSpaceLength);
}

int main() {
    memset(dp, -1, sizeof(dp));
    vector<string> ws = {"ab", "ab", "aaaaa", "aaaaa"};
    cout << makeLines(ws, 0, 10, 1) << "\n\n";
    for (int i = 0; i < 10; ++i) {
        cout << dp[i] << "\n";
    }
}