// https://www.acmicpc.net/problem/13549
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using intp = pair<int, int>;
int main(){
    priority_queue<intp, vector<intp>, greater<intp>> q;
    bool visited[100001] = {0, };

    int n,k;
    cin >> n >> k;

    q.push(make_pair(0, n));  // time, location
    visited[n] = true;
    
    while(!q.empty()){
        auto [time, loc] = q.top();
        q.pop();

        if(loc == k){
            cout << time;
            break;
        }

        for(int x=loc*2; x!=0 && x<=100000; x*=2){
            if(!visited[x]){
                q.push(make_pair(time, x));
                visited[x] = true;
            }
        }
        if(loc < k && !visited[loc+1]){
            q.push(make_pair(time+1, loc+1));
            visited[loc+1] = true;
        }
        if(loc > 0 && !visited[loc-1]){
            q.push(make_pair(time+1, loc-1));
            visited[loc-1] = true;
        }
    }

    return 0;
}

/*
    -- 생각해 볼 것 --
    +1, -1을 계속 반복해서 같은 위치를 중복해서 방문해서 틀렸었다.

    '다음 경우'를 확인하는데 필요한 cost가 동일하면 bfs,dfs
    cost가 다를 경우(가중치가 다를 경우) 다익스트라

    condition을 적을 때, 의심스럽거나 애매하면 주석으로 표시해놓기
    28line에서 x <= k로 했었다가 틀림
        - 5 9 같은 경우 5 > 10 > 9로 앞으로 갔다가 뒤로 한칸 빼는게 빠른 경우
*/