// https://www.acmicpc.net/problem/13334
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;
using intp = pair<int, int>;

int main(){
    intp moves[100000];
    int n, h, o, d;

    cin >> n;
    for(int i=0; i<n; i++){
        cin >> h >> o;

        if(h < o) moves[i] = {h ,o};
        else moves[i] = {o, h};
    }
    cin >> d;

    sort(moves, moves+n, [](const intp& a, const intp& b) -> bool {
        if(a.second == b.second) return a.first < b.first;
        return a.second < b.second;
        // if(a.first == b.first) return a.second < b.second;
        // return a.first < b.first;
    });

    priority_queue<int, vector<int>, greater<int>> q;
    int beg = moves[0].second - d, end = moves[0].second;
    int ans = 0;
    for(int i=0; i<n; i++){
        auto& cur = moves[i];
        if(d < cur.second - cur.first) continue;

        if(beg <= cur.first && cur.second <= end){
            // q.push(cur.first);
        } else if(end < cur.second){
            end = cur.second;
            beg = end - d;

            // q.push(cur.first);
            while(!q.empty() && q.top() < beg)
                q.pop();
        }

        q.push(cur.first);
        ans = max(ans, static_cast<int>(q.size()));
    }

    cout << ans;

    return 0;
}

/*
    -- 생각해 볼 것 --
    참고: https://dev-game-standalone.tistory.com/90

    이런 범위 관련 문제의 경우 종점(끝점)을 기준으로 보통 정렬함
        - 끝점을 기준으로 이동 및 처리를 진행하면, 첫점(끝점 - 길이)보다 현재값이
        더 뒤에 있는지만 판단하면 됨
    
    1번(0 ~ 5), 2번(-5 ~ 10) 처럼 뒤에 오는게 더 넓은 경우(반대도 마찬가지)를 잘 생각해야됨
        - 그래서 이 문제에서는 priority_queue를 이용해 시작점을 q에 넣고 판단
*/