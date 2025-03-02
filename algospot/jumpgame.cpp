// https://www.algospot.com/judge/problem/read/JUMPGAME
#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

int board[100][100] = {0,}, n;
void solve(){
    bool visited[100][100] = {false,};

    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) cin >> board[i][j];

    queue<pair<int,int>> q;
    q.push(make_pair(0, 0));
    visited[0][0] = true;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        int value = board[cur.first][cur.second];

        if(cur.first + value < n && !visited[cur.first + value][cur.second]){
            visited[cur.first + value][cur.second] = true;
            q.push(make_pair(cur.first + value, cur.second));
            if(cur.first + value == n-1 && cur.second == n-1) break;
        }
        if(cur.second + value < n && !visited[cur.first][cur.second + value]){
            visited[cur.first][cur.second + value] = true;
            q.push(make_pair(cur.first, cur.second + value));
            if(cur.first == n-1 && cur.second + value == n-1) break;
        }
    }

    cout << (q.empty() ? "NO" : "YES") << endl;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
    -- 생각 과정 --
    bfs + visited를 통해 한번 방문한 노드 다시 방문하지 않기

    -- 생각해 볼점 --
    이 문제를 단순히 풀면 미친 시간 복잡도가 나옴
        2(오른쪽, 아래) ^ N^2(타일의 갯수) -> O(2^(N^2))
    하지만 가능한 move_from(x,y)는 N^2
        비둘기 집으로 엄청난 중복이 있음

    -- 반성할 점 --
    바로 정답을 맞추긴 했지만, 공부하는 과정인데도 단순하게 풀 경우를 전혀 생각해보지도 않았음
*/