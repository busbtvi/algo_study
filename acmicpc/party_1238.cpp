// https://www.acmicpc.net/problem/1238
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#define INF 123456789
using namespace std;
using intp = pair<int, int>;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> toX(1001, INF), fromX(1001, INF);
    int road[1001][1001];
    int n, m, x;
    
    cin >> n >> m >> x;
    for(int i=0, beg, end, time; i<m; i++){
        cin >> beg >> end >> time;
        road[beg][end] = time;
    }

    priority_queue<intp, vector<intp>, greater<intp>> q;
    vector<bool> visited1(1001, false);
    q.push({0, x});
    fromX[x] = 0;
    while(!q.empty()){
        auto [cost, loc] = q.top();
        q.pop();

        if(visited1[loc]) continue;
        visited1[loc] = true;

        for(int next=1; next<=n; next++){
            // 길이 있고 && loc에서 next를 거쳐가는게 더 빠를 때
            if(road[loc][next] && fromX[loc]+road[loc][next] < fromX[next]){
                fromX[next] = fromX[loc] + road[loc][next];
                q.push({fromX[next], next});
            }
        }
    }

    vector<bool> visited2(1001, false);
    q.push({0, x});
    toX[x] = 0;
    while(!q.empty()){
        auto [cost, loc] = q.top();
        q.pop();

        if(visited2[loc]) continue;
        visited2[loc] = true;

        for(int prev=1; prev<=n; prev++){
            if(road[prev][loc] && toX[loc]+road[prev][loc] < toX[prev]){
                toX[prev] = toX[loc] + road[prev][loc];
                q.push({toX[prev], prev});
            }
        }
    }

    // for(int i=0; i<=n; i++)
    //     cout << toX[i] << ' ';
    // cout << '\n';
    int ans = 0;
    for(int i=1; i<=n; i++)
        ans = max(ans, fromX[i] + toX[i]);
    cout << ans;

    return 0;
}

/*
    -- 생각 과정 --
    무식하게: 다익스트라 * n -> n^3
    플로이드 와샬: n^3

    다익스트라 최단 거리 테이블을 끊지않고, 모든 목적지에 대해서 채우기
        -> x로부터 나머지로 가는 최단 경로
    다익스트라를 역으로 생각해서 x로 오는 최단 경로 계산
    두개 합치기

    -- 주의 할 점 --
    다익스트라 할 때, !!방문했는지 여부 확인 할 것!!
*/