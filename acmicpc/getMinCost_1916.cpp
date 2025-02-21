// https://www.acmicpc.net/problem/1916
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

int main(){
    int n, m, beg, end;
    cin >> n >> m;

    vector<vector<int>> costs(n+1, vector<int>(n+1, INT_MAX));
    vector<int> minCost(n+1, INT_MAX), visited(n+1, 0);
    for(int i=0, s,e,c; i<m; i++){
        cin >> s >> e >> c;

        if(costs[s][e]==INT_MAX || c<costs[s][e])
            costs[s][e] = c;
    }
    cin >> beg >> end;

    minCost[beg] = 0;
    visited[beg] = 1;
    for(int cur=beg; cur!=end; ){
        for(int i=1; i<=n; i++){
            if(visited[i]) continue;
            if(costs[cur][i] != INT_MAX && minCost[cur]+costs[cur][i]<minCost[i]){
                minCost[i] = minCost[cur] + costs[cur][i];
            }
        }

        for(int i=1, minDist = INT_MAX; i<=n; i++){
            if(visited[i]) continue;
            if(minCost[i] < minDist){
                minDist = minCost[i];
                cur = i;
            }
        }

        visited[cur] = 1;
    }

    cout << minCost[end];

    return 0;
}