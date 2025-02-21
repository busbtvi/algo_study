// https://www.acmicpc.net/problem/2098
#include <iostream>
#include <map>
#define INTMAX 100000000
using namespace std;

int costs[16][16], n;
map<int, map<int,int>> dp;  // dp[방문 안한 도시들][현재 위치] = minCost(남은도시->출발지로)
int dfsSearch(int prevI, int notVisited){
    if(notVisited == 0) return costs[prevI][0] ? costs[prevI][0] : INTMAX;

    int localMin = INTMAX;
    for(int curI=1; curI<n; curI++){
        if(((notVisited >> curI) & 1) && costs[prevI][curI]){
            notVisited &= ~(1 << curI);

            if(dp[notVisited].find(curI) == dp[notVisited].end())
                dp[notVisited][curI] = dfsSearch(curI, notVisited);

            if(localMin > costs[prevI][curI] + dp[notVisited][curI])
                localMin = costs[prevI][curI] + dp[notVisited][curI];
            
            notVisited |= (1 << curI);
        }
    }
    dp[notVisited][prevI] = localMin;
    return localMin;
}

int main(){
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> costs[i][j];

    cout << dfsSearch(0, (0xFFFF >> (17-n)) << 1);

    return 0;
}