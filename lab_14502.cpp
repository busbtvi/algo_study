// https://www.acmicpc.net/problem/14502
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
int lab[8][8] = {0,}, n,m;
int ans = 0;

void countSafeArea(){
    int copyLab[8][8] = {0,};
    int safeAreaCount = 0;
    queue<pair<int,int>> bfsQ;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            copyLab[i][j] = lab[i][j];

            if(copyLab[i][j] == 2){
                bfsQ.push({i, j});
            }
            else if(copyLab[i][j] == 0) safeAreaCount++;
        }
    }
    
    while(!bfsQ.empty()){
        int i = bfsQ.front().first, j = bfsQ.front().second;
        bfsQ.pop();

        for(int tempI = i-1; tempI <= i+1; tempI += 2){
            if(tempI>=0 && tempI<n && copyLab[tempI][j] == 0){
                copyLab[tempI][j] = 2;
                bfsQ.push({tempI, j});
                safeAreaCount--;
            }
        }
        for(int tempJ = j-1; tempJ <= j+1; tempJ += 2){
            if(tempJ>=0 && tempJ<m && copyLab[i][tempJ] == 0){
                copyLab[i][tempJ] = 2;
                bfsQ.push({i, tempJ});
                safeAreaCount--;
            }
        }
    }

    if(safeAreaCount > ans) ans = safeAreaCount;
}

void setWall(int wallCount){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(lab[i][j] == 0){
                lab[i][j] = 1;
                if(wallCount == 2) countSafeArea();
                else setWall(wallCount+1);
                lab[i][j] = 0;
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cin >> lab[i][j];
    }
    
    setWall(0);
    cout << ans << '\n';

    return 0;
}