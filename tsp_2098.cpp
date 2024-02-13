// https://www.acmicpc.net/problem/2098
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int permutation[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int costs[16][16], n, ans = ~(1<<31);
void dfsSearch(int prevI, int prevCost){
    if(prevI == n-2 && costs[permutation[n-2]][permutation[n-1]] && costs[permutation[n-1]][0]){
        // back to start
        if(ans > prevCost + costs[permutation[n-2]][permutation[n-1]] + costs[permutation[n-1]][0]){
            ans = prevCost + costs[permutation[n-2]][permutation[n-1]] + costs[permutation[n-1]][0];
        }
        return;
    }
    if(prevCost > ans) return;

    for(int i=prevI+1; i<n; i++){
        if(costs[permutation[prevI]][permutation[i]]){
            swap(permutation[prevI+1], permutation[i]);
            dfsSearch(prevI+1, prevCost + costs[permutation[prevI]][permutation[prevI+1]]);
            swap(permutation[prevI+1], permutation[i]);
        }
    }
}

int main(){
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> costs[i][j];

    dfsSearch(0, 0);
    cout << ans;

    return 0;
}