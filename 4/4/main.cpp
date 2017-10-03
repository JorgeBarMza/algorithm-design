//
//  main.cpp
//  4
//
//  Created by Jorge Barrios on 10/2/17.
//  Copyright © 2017 Jorge Barrios. All rights reserved.
//

#include <iostream>
#include <vector>
#define n 3
using namespace std;

vector<vector<int>> men(n,vector<int>(n,-1)), women(n,vector<int>(n,-1));

vector<int>  stableCouples(){
    vector<int> engaged(n,-1);
    vector<bool> married(n,false);
    int singleMen = n;
    while(singleMen){
        for(int m = 0; m<n; m++){
            if(married[m] == true )
                continue;
            for (int w = 0; w<n; w++) {
                int sexyLady = men[m][w];
                if(engaged[sexyLady] == -1){
                    engaged[sexyLady] = m;
                    married[m] = true;
                    singleMen--;
                    break;
                }
                else{ // check if marriage is unstable
                    int p = *find(women[sexyLady].begin(), women[sexyLady].end(), engaged[sexyLady]);
                    int newHusband = *find(women[sexyLady].begin(), women[sexyLady].end(), m);
                    if(newHusband < p){
                        engaged[sexyLady] = m;
                        married[m] = true;
                        married[engaged[sexyLady]] = false;
                        break;
                    }
                }
            }
        }
    }
    return engaged;
}

int main() {
    
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
//            cin >> men[i][j];
            men[i][j] = j;
        }
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
//            cin >> women[i][j];
            women[i][j] = j;
        }
    }
    
    vector<int> res = stableCouples();
    for(int i=0; i<res.size(); ++i){
        cout << "Woman #" << i << " is married to Husband #" << res[i] << "\n";
    }
}



