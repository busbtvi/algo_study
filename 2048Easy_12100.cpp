// https://www.acmicpc.net/problem/12100
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    queue<vector<vector<int>>> dfs;
    int n, maxNum=0;
    cin >> n;

    vector<vector<int>> init(n, vector<int>(n, 0));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) cin >> init[i][j];
    dfs.push(init);

    for(int move=0; move<5; move++){
        for(int i=0, qSize=dfs.size(); i<qSize; i++){
            vector<vector<int>> cur(dfs.front());

            // left
            vector<vector<int>> left(n, vector<int>(n, 0));
            for(int row=0; row<n; row++){
                for(int nextCol=0,j=0,k=0; k<n; nextCol++){
                    while(j<n && cur[row][j]==0) j++;
                    if(j == n) break;

                    k = j+1;
                    while(k<n && cur[row][k]==0) k++;

                    if(k<n && cur[row][j] == cur[row][k]){
                        left[row][nextCol] = cur[row][j] * 2;
                        j = k+1;
                    }
                    else{
                        left[row][nextCol] = cur[row][j];
                        j = k;
                    }
               }
            }
            // right
            vector<vector<int>> right(n, vector<int>(n, 0));
            for(int row=n-1; row>=0; row--){
                for(int nextCol=n-1,j=n-1,k=n-1; k>=0; nextCol--){
                    while(j>=0 && cur[row][j]==0) j--;
                    if(j == -1) break;

                    k = j-1;
                    while(k>=0 && cur[row][k]==0) k--;

                    if(k>=0 && cur[row][j] == cur[row][k]){
                        right[row][nextCol] = cur[row][j] * 2;
                        j = k-1;
                    }
                    else{
                        right[row][nextCol] = cur[row][j];
                        j = k;
                    }
               }
            }
            
            // up
            vector<vector<int>> up(n, vector<int>(n, 0));
            for(int col=0; col<n; col++){
                for(int nextRow=0,j=0,k=0; k<n; nextRow++){
                    while(j<n && cur[j][col]==0) j++;
                    if(j == n) break;

                    k = j+1;
                    while(k<n && cur[k][col]==0) k++;

                    if(k<n && cur[j][col] == cur[k][col]){
                        up[nextRow][col] = cur[j][col] * 2;
                        j = k+1;
                    }
                    else{
                        up[nextRow][col] = cur[j][col];
                        j = k;
                    }
               }
            }
            // down
            vector<vector<int>> down(n, vector<int>(n, 0));
            for(int col=n-1; col>=0; col--){
                for(int nextRow=n-1,j=n-1,k=n-1; k>=0; nextRow--){
                    while(j>=0 && cur[j][col]==0) j--;
                    if(j == -1) break;

                    k = j-1;
                    while(k>=0 && cur[k][col]==0) k--;

                    if(k>=0 && cur[j][col] == cur[k][col]){
                        down[nextRow][col] = cur[j][col] * 2;
                        j = k-1;
                    }
                    else{
                        down[nextRow][col] = cur[j][col];
                        j = k;
                    }
               }
            }

            if(move == 4){
                for(auto r: left) for(auto c: r) if(c > maxNum) maxNum = c;
                for(auto r: right) for(auto c: r) if(c > maxNum) maxNum = c;
                for(auto r: up) for(auto c: r) if(c > maxNum) maxNum = c;
                for(auto r: down) for(auto c: r) if(c > maxNum) maxNum = c;
            }
            else{
                dfs.push(left); dfs.push(right);
                dfs.push(up);   dfs.push(down);
            }

            dfs.pop();
        }
        
    }

    cout << maxNum;
    return 0;
}
// 한방에 맞긴 했지만 https://forward-gradually.tistory.com/83