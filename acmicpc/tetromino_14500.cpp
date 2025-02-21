// https://www.acmicpc.net/problem/14500
#include <iostream>
#include <utility>
#include <limits.h>
using namespace std;

int udlr[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};  // UpDownLeftRight
int n, m, paper[500][500];
bool visited[500][500] = {0,};

int getMaxScore(int depth, int i, int j, int score){
    if(depth == 5) return score;
    if(visited[i][j]) return INT_MIN;
    visited[i][j] = true;

    int curMax = INT_MIN;
    for(int k=0, ni, nj; k<4; k++){
        ni = i + udlr[k][0];
        nj = j + udlr[k][1];
        
        if(ni<0 || ni>=n || nj<0 || nj>=m) continue;
        curMax = max(curMax, getMaxScore(depth+1, ni, nj, score+paper[i][j]));
    }
    visited[i][j] = false;

    return curMax;
}
int getMaxScore_T(){
    int curMax = INT_MIN;

    for(int i=1; i<n-1; i++){
        for(int j=1, curSum; j<m-1; j++){
            curSum = paper[i][j] + paper[i-1][j] + paper[i+1][j] + paper[i][j-1] + paper[i][j+1] 
                    - min(min(paper[i-1][j], paper[i+1][j]), min(paper[i][j-1], paper[i][j+1]));
            curMax = max(curMax, curSum);
        }
    }

    for(int j=1, up, down; j<m-1; j++){
        up   = paper[n-1][j-1] + paper[n-1][j] + paper[n-1][j+1] + paper[n-2][j];
        down = paper[0][j-1] + paper[0][j] + paper[0][j+1] + paper[1][j];
        curMax = max(curMax, max(up, down));
    }
    for(int i=1, left, right; i<n-1; i++){
        left  = paper[i-1][0] + paper[i][0] + paper[i+1][0] + paper[i][1];
        right = paper[i-1][n-1] + paper[i][n-1] + paper[i+1][n-1] + paper[i][n-2];
        curMax = max(curMax, max(left, right));
    }

    return curMax;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> paper[i][j];

    int ans = INT_MIN;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            ans = max(ans, getMaxScore(1, i, j, 0));
        
    ans = max(ans, getMaxScore_T());
    cout << ans;

    return 0;
}