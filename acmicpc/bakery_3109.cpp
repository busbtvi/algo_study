// https://www.acmicpc.net/problem/3109
#include <iostream>
using namespace std;

int r, c, ans = 0, minColPass = 5000;
int colPass[500] = {0,};
char mapData[10000][500];
bool visited[10000][500]= {0,};
bool dfs(int i, int j){
    if(j == c-1) return true;

    for(int nextI=i-1; nextI<i+2; nextI++){
        if(nextI < 0 || nextI >= r) continue;

        if(mapData[nextI][j+1] == '.' && !visited[nextI][j+1]){
            visited[nextI][j+1] = true;
            if(dfs(nextI, j+1)) return true;
            // visited[nextI][j+1] = false;
        }
    }
    visited[i][j] = true;
    return false;
}

int main(){
    cin >> r >> c;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++){
            cin >> mapData[i][j];
            if(mapData[i][j] == '.') colPass[j]++;
        }

    for(int j=0; j<c; j++) minColPass = min(minColPass, colPass[j]);
    for(int i=0; i<r; i++){
        if(dfs(i, 0)) ans++;
        if(minColPass == ans) break;
    }
    cout << ans;

    return 0;
}