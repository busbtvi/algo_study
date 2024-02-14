// https://www.acmicpc.net/problem/2206
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

int costs[1000][1000][2] = {0,};  // [row][col][breakWall] = cost
int main(){
    char mapData[1000][1000] = {0,};
    int dir[4][2] = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
    int n, m, ans = -1;
    queue<tuple<int,int,int>> bfsQ;  // row, col, breakWall

    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) cin >> mapData[i][j];

    bfsQ.push(make_tuple(0,0,0));
    costs[0][0][0] = 1;
    while(!bfsQ.empty()){
        int i, j, wallBreak;
        tie(i,j,wallBreak) = bfsQ.front();

        if(i==n-1 && j==m-1){
            ans = costs[n-1][m-1][wallBreak];
            break;
        }

        for(int k=0; k<4; k++){
            int newI = i + dir[k][0];
            int newJ = j + dir[k][1];

            if(newI>=0 && newI<n && newJ>=0 && newJ<m){
                if(costs[newI][newJ][wallBreak] == 0){
                    if(mapData[newI][newJ] == '1'){
                        if(wallBreak == 0){
                            bfsQ.push(make_tuple(newI, newJ, 1));
                            costs[newI][newJ][1] = costs[i][j][0] + 1;
                        }
                    }
                    else{
                        bfsQ.push(make_tuple(newI, newJ, wallBreak));
                        costs[newI][newJ][wallBreak] = costs[i][j][wallBreak] + 1;
                    }
                }
            }
        }
        bfsQ.pop();
    }

    cout << ans;

    return 0;
}