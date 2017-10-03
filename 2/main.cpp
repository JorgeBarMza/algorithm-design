#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;
int dp[100]; //100 words max
vector<struct line> lines;

struct line{
    int startW;
    int endW;
    int spaceLength;
};

int calcBadness(line& curr, vector<string>& words, int firstW, int lastW, int lineLenght, int optimalSpaceLength){
    int remainingLength = lineLenght, individualSpaceLength = 1;
    int wordCount = lastW-firstW+1;
    for (int i = firstW; i <= lastW ; ++i) {
        remainingLength -= (words[i].size() + 1);
    }
    remainingLength++; //last word of line has no space
    if(0 <= remainingLength && lastW == words.size()-1){
        curr.spaceLength = individualSpaceLength;
        return 0;
    }
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
    curr.spaceLength = individualSpaceLength;
    return (lastW-firstW) * abs(individualSpaceLength - optimalSpaceLength);
}

int makeLines(vector<string> words,  int index, int lineLength, int optimalSpaceLength) {
    if(index == words.size())
        return 0;
    if(dp[index] != -1)
        return dp[index];
    int minBadness = INT32_MAX, nextWord;
    line toAdd;
    for (int i = index; i < words.size(); ++i) {
        line curr;
        curr.startW = index;
        curr.endW = i;
        int badness = calcBadness(curr, words, index, i, lineLength, optimalSpaceLength);
        if(badness < minBadness){
            minBadness = badness;
            nextWord = i+1;
            toAdd = curr;
        }
    }
    lines.push_back(toAdd);
    return dp[index] = minBadness + makeLines(words, nextWord, lineLength, optimalSpaceLength);
}

int main() {
    memset(dp, -1, sizeof(dp));
    vector<string> ws = {"aaa", "aae", "aa", "aaa", "aaa", "aa"};
    cout << "Cost: " << makeLines(ws, 0, 10, 1) << "\n\n";
    cout << "Justified Text:\n";
//    for (int i = 0; i < 10; ++i) {
//        cout << dp[i] << "\n";
//    }
    int currLine = 0;
    for(auto line:lines){
        for (int i = line.startW; i < line.endW ; ++i) {
            cout << ws[i];
            for (int j = 0; j < line.spaceLength ; ++j) {
                cout << " ";
            }
        }
        cout << ws[line.endW] << "\n"; // last word no space
    }
}