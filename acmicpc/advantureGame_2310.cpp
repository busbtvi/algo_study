// https://www.acmicpc.net/problem/2310
#include <iostream>
#include <queue>
using namespace std;
using intp = pair<int, int>;

void solve(int n){
    // 동일한 방을 더 많은 돈으로 방문하면, 다시 생각해야 됨
    vector<int> visitedWithMoney(n+1, -1);
    vector<int> rooms(n+1, 0);
    vector<vector<int>> path(n+1);

    char type;
    for(int i=1, cost, next; i<=n; i++){
        cin >> type >> cost >> next;

        rooms[i] = type == 'T' ? -cost : cost;
        while(next){
            path[i].push_back(next);
            cin >> next;
        }
    }

    priority_queue<intp> q;  // cost, current
    q.push(make_pair(0, 0));
    // visitedWithMoney[0] = -1;
    path[0].push_back(1);  // can move to 1'st room

    while(!q.empty()){
        intp cur = q.top(), temp;
        q.pop();

        // cout << "q.top = " << cur.first << ' ' << cur.second << ' ' << visitedWithMoney[cur.second] << endl;
        if(cur.second == n){
            cout << "Yes\n";
            return;
        }

        for(auto& next: path[cur.second]){
            if(cur.first <= visitedWithMoney[next]) continue;
            if(rooms[next] + cur.first < 0) continue;  // currentMoney < T

            if(0 < rooms[next])  // L -> max(가진것, 레프리콘)
                temp = make_pair(max(cur.first, rooms[next]), next);
            else  // E or T < correntMoney
                temp = make_pair(cur.first + rooms[next], next);

            visitedWithMoney[next] = temp.first;
            q.push(temp);
        }
    }

    cout << "No\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;

    cin >> n;
    while(n != 0){
        solve(n);
        cin >> n;
    }
}

/*
    -- 생각 과정 --
    bfs로 풀면 될듯? O(N^2) 나오는거 같은데
    같은곳을 다시 방문할 필요가 있나? 없는듯?

    동일한 위치를 더 많은 금액으로 방문할때'만' 다시 확인하게 하기
*/