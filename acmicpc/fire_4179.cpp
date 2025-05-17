// https://www.acmicpc.net/problem/4179
#include <iostream>
#include <utility>
#include <queue>
using namespace std;
using intp = pair<int, int>;

int r, c, day = 0;
char board[1000][1000] = {0, };
bool visited[1000][1000] = {false, };
int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int main(){
    queue<intp> jihun, fire;

    cin >> r >> c;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cin >> board[i][j];

            if(board[i][j] == 'J'){
                board[i][j] = '.';
                jihun.push({i, j});
                visited[i][j] = true;
            }
            else if(board[i][j] == 'F'){
                fire.push({i, j});
            }
        }
    }
    
    while(!jihun.empty()){
        day++;
        for(int beg=0, end=fire.size(); beg<end; beg++){
            auto [i, j] = fire.front();
            fire.pop();

            for(int m=0; m<4; m++){
                int ni = i + dir[m][0], nj = j + dir[m][1];
    
                if(0<=ni && ni<r && 0<=nj && nj<c){
                    if(board[ni][nj] == '.'){
                        board[ni][nj] = 'F';
                        fire.push({ni, nj});
                    }
                }
            }
        }

        for(int beg=0, end=jihun.size(); beg<end; beg++){
            auto [i, j] = jihun.front();
            jihun.pop();
            
            if(i==0 || i==r-1 || j==0 || j==c-1){
                cout << day << endl;
                return 0;
            }

            for(int m=0; m<4; m++){
                int ni = i + dir[m][0], nj = j + dir[m][1];
                
                if(0<=ni && ni<r && 0<=nj && nj<c){
                    if(!visited[ni][nj] && board[ni][nj] == '.'){
                        visited[ni][nj] = true;
                        jihun.push({ni, nj});
                    }
                }
            }
        }
    }
    
    cout << "IMPOSSIBLE\n";

    return 0;
}

/*
    -- 접근 방식 --
    불은 불대로 퍼지고, J만 bfs로 탐색하면 되는건가?
        -> 맞긴 했는데, 불이 먼저 움직여야됨
    
    -- 생각해 볼 것 --
    각 위치에 불이 붙는 시간을 나타내는 맵을 먼저 만들고,
    사람이 해당 위치에 도달하는 시간보다 불이 빠르면 이동 불가
    이렇게 생각했어도 됨
*/