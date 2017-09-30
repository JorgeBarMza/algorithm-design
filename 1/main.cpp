#include <iostream>
#include <vector>
using namespace std;

vector<int> paradas(int totalDist, int n, vector<int> gas){
    int currDist = 0, nextGasIndex = 0;
    gas.push_back(totalDist);
    vector<int> paradas;
    while(currDist+n < totalDist){
        if(gas[nextGasIndex+1] > n + currDist){
            if(gas[nextGasIndex] > n + currDist)
                throw invalid_argument("gasolineras muy separadas");
            paradas.push_back(gas[nextGasIndex]);
            currDist = gas[nextGasIndex];
        }
        nextGasIndex++;
    }
    return paradas;
}

int main() {
    vector<int> d = {1};
    try{
        vector<int> a = paradas(3, 3, d);
    }
    catch(invalid_argument &e){
        cout << e.what();
    }
}

