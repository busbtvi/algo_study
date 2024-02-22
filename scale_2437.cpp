// https://www.acmicpc.net/problem/2437
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n, weights[1000], curMax = 0;

    cin >> n;
    for(int i=0; i<n; i++) cin >> weights[i];
    sort(weights, weights+n);

    for(int i=0; i<n; i++){
        if(curMax+1 >= weights[i]){
            curMax += weights[i];
        }
        else break;
    }
    cout << curMax + 1;

    return 0;
}