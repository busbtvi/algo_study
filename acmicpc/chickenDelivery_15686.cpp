// https://www.acmicpc.net/problem/15686
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<pair<int,int>> chickenStore, houses;
    vector<int> combination;
    int n, m, ans = ~(1<<31);
    cin >> n >> m;

    chickenStore.reserve(n*n); 
    houses.reserve(n*n);
    for(int i=0; i<n; i++){
        for(int j=0, k; j<n; j++){
            cin >> k;

            if(k == 2) chickenStore.push_back({i,j});
            else if(k == 1) houses.push_back({i, j});
        }
    }

    for(int i=0; i<chickenStore.size(); i++) combination.push_back(i<m);
    // for(int i=0; i<chickenStore.size(); i++) cout << combination[i] << ' ';
    do{
        int totalChickenDistance = 0;
        for(auto house: houses){
            int minDist = 100, curDist;
            for(int i=0; i<combination.size(); i++){
                if(combination[i]){
                    curDist = abs(house.first - chickenStore[i].first) + abs(house.second - chickenStore[i].second);
                    if(minDist > curDist) minDist = curDist;
                }
            }
            totalChickenDistance += minDist;
        }

        if(totalChickenDistance < ans) ans = totalChickenDistance;
    }while(prev_permutation(combination.begin(), combination.end()));

    cout << ans;

    return 0;
}