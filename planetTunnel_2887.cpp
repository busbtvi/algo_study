//  https://www.acmicpc.net/problem/2887
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> vertex;
int getRoot(int i){
    if(vertex[i] != i) vertex[i] = getRoot(vertex[i]);
    return vertex[i];
}

int main(){
    using intp = pair<int,int>;
    using intt = tuple<int,int,int>;
    int n, ans = 0;
    cin >> n;

    vector<vector<intp>> xyz(3, vector<intp>(n, {0,0}));  // index, coordinate
    vector<vector<intt>> edges(3, vector<intt>(n-1, {0,0,0}));  // cost, beg, end
    for(int i=0, a,b,c; i<n; i++){
        cin >> xyz[0][i].second >> xyz[1][i].second >> xyz[2][i].second;
        xyz[0][i].first = xyz[1][i].first = xyz[2][i].first = i;
    }

    // 어쨌든 연결만 되면 되니, 각 vertex는 자신과 가장 가까운 vertex에 연결 되기만 하면 됨
    // 그럼 n*(n-3)의 edge가 아니라, 3*(n-1)만 탐색
    for(int i=0; i<3; i++){
        sort(xyz[i].begin(), xyz[i].end(), [](const intp& a, const intp& b){
            return a.second < b.second;
        });
        for(int j=1; j<xyz[i].size(); j++)
            edges[i][j-1] = make_tuple(xyz[i][j].second - xyz[i][j-1].second, xyz[i][j].first, xyz[i][j-1].first);
        sort(edges[i].begin(), edges[i].end(), [](const intt& a, const intt& b){
            return get<0>(a) < get<0>(b);
        });
    } 

    vertex.reserve(n);
    for(int i=0; i<n; i++) vertex[i] = i;
    for(int connect=0, xi=0, yi=0, zi=0; connect<n-1;){
        // iterate like merge sort
        intt cur;
        if(get<0>(edges[0][xi])<=get<0>(edges[1][yi]) && get<0>(edges[0][xi])<=get<0>(edges[2][zi]))
            cur = edges[0][xi++];
        else if(get<0>(edges[1][yi]) <= get<0>(edges[2][zi]))
            cur = edges[1][yi++];
        else cur = edges[2][zi++];

        if(getRoot(get<1>(cur)) != getRoot(get<2>(cur))){
            if(vertex[get<1>(cur)] < vertex[get<2>(cur)])
                vertex[vertex[get<2>(cur)]] = vertex[get<1>(cur)];
            else vertex[vertex[get<1>(cur)]] = vertex[get<2>(cur)];

            ans += get<0>(cur);
            connect++;
        }
    }

    cout << ans;
    // for(int i=0; i<3; i++){
    //     for(auto a: xyz[i]){
    //         cout << a.second << ' ';
    //     }
    //     cout << '\n';
    // }

    return 0;
}