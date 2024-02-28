// https://www.acmicpc.net/problem/10282
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <map>
using namespace std;

void hacking(){
    using intp = pair<int,long long>;
    auto comp = [](const intp& a, const intp& b){
        return a.second > b.second;
    };

    bool isHacked[10001] = {0,};
    int n,d,c, hackedCount = 1;
    long long hackingTime = 0;
    // 누구에게, 누가의존하고, 감염에 걸리는 시간
    map<int, vector<intp>> dependency;
    // 현재 컴퓨터, 지금까지 걸린 시간
    priority_queue<intp, vector<intp>, decltype(comp)> hacking(comp); 

    cin >> n >> d >> c;
    for(int i=0,a,b,s; i<d; i++){
        cin >> a >> b >> s;

        dependency[b].push_back({a,s});
    }

    isHacked[c] = true;
    for(auto i: dependency[c]) hacking.push({i.first, i.second});
    while(!hacking.empty()){
        auto cur = hacking.top();
        hacking.pop();

        if(isHacked[cur.first]) continue;

        isHacked[cur.first] = true;
        hackedCount++;
        for(auto i: dependency[cur.first]) 
            hacking.push({i.first, cur.second + i.second});
        if(cur.second > hackingTime) hackingTime = cur.second;
    }

    cout << hackedCount << ' ' << hackingTime << '\n';
}

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++) hacking();
    return 0;
}