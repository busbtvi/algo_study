// https://www.acmicpc.net/problem/16234
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

int a[50][50] = {0, }, n, l, r;
bool movePopulation(){
    bool visited[50][50] = {0, };

    vector<vector<pair<int,int>>> unions;
    vector<int> sums;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]) continue;

            vector<pair<int,int>> cur;
            queue<pair<int, int>> q;
            
            cur.push_back({i, j});
            q.push({i, j});
            visited[i][j] = true;
            int acc = a[i][j];

            // cout << "\nvisit " << i << ' ' << j << '\n';
            while(!q.empty()){
                auto [row, col] = q.front();
                q.pop();
                
                if(row+1 < n && !visited[row+1][col]){
                    int gap = abs(a[row][col] - a[row+1][col]);
                    if(l <= gap && gap <= r){
                        cur.push_back({row+1, col});
                        q.push({row+1, col});
                        visited[row+1][col] = true;
                        acc += a[row+1][col];

                        // cout << "push " << row+1 << ' ' << col << '\n';
                    }
                }
                if(row-1 >= 0 && !visited[row-1][col]){
                    int gap = abs(a[row][col] - a[row-1][col]);
                    if(l <= gap && gap <= r){
                        cur.push_back({row-1, col});
                        q.push({row-1, col});
                        visited[row-1][col] = true;
                        acc += a[row-1][col];

                        // cout << "push " << row-1 << ' ' << col << '\n';
                    }
                }
                if(col+1 < n && !visited[row][col+1]){
                    int gap = abs(a[row][col] - a[row][col+1]);
                    if(l <= gap && gap <= r){
                        cur.push_back({row, col+1});
                        q.push({row, col+1});
                        visited[row][col+1] = true;
                        acc += a[row][col+1];

                        // cout << "push " << row << ' ' << col+1 << '\n';
                    }
                }
                if(col-1 >= 0 && !visited[row][col-1]){
                    int gap = abs(a[row][col] - a[row][col-1]);
                    if(l <= gap && gap <= r){
                        cur.push_back({row, col-1});
                        q.push({row, col-1});
                        visited[row][col-1] = true;
                        acc += a[row][col-1];

                        // cout << "push " << row << ' ' << col-1 << '\n';
                    }
                }
            }

            if(cur.size() > 1){
                unions.push_back(cur);
                sums.push_back(acc);
            }
        }
    }
    
    if(!unions.empty()){  // update population
        for(int i=0; i<unions.size(); i++){
            int avg = sums[i] / unions[i].size();

            for(auto [row, col]: unions[i])
                a[row][col] = avg;
        }
    }

    // cout << "union size: " << unions.size() << '\n';
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++) cout << a[i][j] << ' ';
    //     cout << '\n';
    // }
    // cout << endl;
    // return unions.size();// ? unions.size() : prevUnionCount;
    return !unions.empty();
}
int main(){
    int ans = 0, populationCount = 0;

    cin >> n >> l >> r;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];

    while(movePopulation()) ans++;
    cout << ans << '\n';

    return 0;
}

/*
    -- 접근 방식 --
    브루트포스 + union find: 50^2 * 2,000일
*/