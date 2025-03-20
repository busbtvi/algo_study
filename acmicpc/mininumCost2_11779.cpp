// https://www.acmicpc.net/problem/11779
#include <iostream>
#include <memory.h>
#include <string>
#include <map>
#include <queue>
#include <utility>
#define INF 123456789

using namespace std;
using intp = pair<int, int>;


map<int, map<int,int>> bus;
void shortest_path(int beg, int end){
    vector<int> min_cost(1001, INF);
    vector<int> path_count(1001, 0);
    string path_history[1001];
    priority_queue<intp, vector<intp>, greater<intp>> q;  // 거리, 현재 위치
    
    path_history[beg] = to_string(beg);
    path_count[beg] = 1;
    min_cost[beg] = 0;
    q.push(make_pair(0, beg));

    while(!q.empty()){
        auto cur_pair = q.top();
        int cur = cur_pair.second;
        
        if(cur == end) break;
        q.pop();

        // 현재 위치에서 갈 수 있는 다음 후보들
        for(auto& next_cand: bus[cur]){  
            int next = next_cand.first, cost = next_cand.second;

            if(min_cost[cur]+cost < min_cost[next]){
                min_cost[next]      = min_cost[cur] + cost;
                path_history[next]  = path_history[cur] + " " + to_string(next);
                path_count[next]    = path_count[cur] + 1;
                q.push(make_pair(min_cost[next], next));
            }
        }
    }

    cout << min_cost[end] << '\n' << path_count[end] << '\n' << path_history[end] << endl;
}
int main(){
    int n, m, ans_beg, ans_end;

    // read input
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int beg, end, cost;
        cin >> beg >> end >> cost;

        if(bus.find(beg) != bus.end() && bus[beg].find(end) != bus[beg].end() && bus[beg][end] < cost)
            continue;
        bus[beg][end] = cost;
    }
    cin >> ans_beg >> ans_end;

    shortest_path(ans_beg, ans_end);

    return 0;
}

/*
    -- 생각 과정 --
    그래프 문제에 다익스트라 인듯?

    -- 틀린 이유 --
    동일한 path(beg, end가 같은)에서 cost가 다른 길이 존재 가능
*/