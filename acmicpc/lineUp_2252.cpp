// https://www.acmicpc.net/problem/2252
#include <iostream>
#include <queue>
#include <map>
#include <vector>
using namespace std;

int main(){
    // students는 위상정렬 진입차수를 저장
    int n, m, students[32001] = {0,};
    map<int, vector<int>> compared;
    queue<int> q;
    cin >> n >> m;

    for(int i=0, a,b; i<m; i++){
        cin >> a >> b;
        students[b]++;
        compared[a].push_back(b);
    }

    for(int i=1; i<=n; i++)
        if(students[i] == 0) q.push(i);
    while(!q.empty()){
        cout << q.front() << ' ';
        for(auto i: compared[q.front()]){
            students[i]--;
            if(students[i] == 0) q.push(i);
        }

        q.pop();
    }

   return 0;
}