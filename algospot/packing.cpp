// https://www.algospot.com/judge/problem/read/PACKING
#include <iostream>
#include <memory.h>
#include <cassert>
#include <tuple>
#include <string>
#include <vector>
using namespace std;

// 이름, 부피, 절박도(점수)
vector<tuple<string, int, int>> objects;
int cache[100][1001], n, w;
int recursive(int cur, int remain){
    if(cur == n || remain == 0) return 0;

    int& ans = cache[cur][remain];
    if(ans == 0){
        int without_cur = recursive(cur+1, remain);
        int with_cur = (get<1>(objects[cur]) > remain) ? 0 :
            get<2>(objects[cur]) + recursive(cur + 1, remain - get<1>(objects[cur]));

        ans = max(with_cur, without_cur);
    }

    return ans;
}
int print(int cur, int remain, bool print_name){
    // cout << endl;
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<=w; j++) cout << cache[i][j] << ' ';
    //     cout << endl;
    // }
    if(cur == objects.size()-1){
        if(remain < get<1>(objects[cur])) return 0;
        if(print_name) cout << get<0>(objects[cur]) << endl;
        return 1;
    }

    if(cache[cur][remain] == cache[cur+1][remain])
        return print(cur+1, remain, print_name);

    if(print_name) cout << get<0>(objects[cur]) << endl;
    return 1 + print(cur+1, remain - get<1>(objects[cur]), print_name);
}
void solve(){
    cin >> n >> w;
    memset(cache, 0, sizeof(cache));
    objects.clear(); objects.reserve(n);
    
    string name;
    int object_size, object_score;
    for(int i=0; i<n; i++){
        cin >> name >> object_size >> object_score;
        objects.push_back(make_tuple(name, object_size, object_score));
    }

    cout << recursive(0, w) << ' ' << print(0, w, false) << endl;
    print(0, w, true);
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    앞에서 물건을 하나씩 선택해가기?
    답을 재구성 하는 과정이 좀 어렵네..

    -- 의문 사항 --
    코드는 책이랑 다른 부분이 없는거 같은데, 내가 틀린건가? 
    아래의 테스트 케이스의 첫번째 처럼 (_1, _2) / (_3) 갯수가 다른데
    절박도가 같은 경우는 맞게 처리하는 건가?
*/
/*
4
3 30
_1 10 10
_2 20 20
_3 30 30
37 240
0 34 66
1 66 76
2 53 53
3 88 71
4 4 62
5 77 17
6 25 31
7 50 58
8 57 71
9 94 87
10 1 9
11 18 95
12 93 24
13 44 57
14 19 19
15 55 8
16 82 72
17 71 77
18 66 77
19 63 51
20 86 38
21 8 82
22 73 23
23 60 64
24 11 42
25 71 77
26 28 45
27 6 2
28 1 22
29 7 26
30 48 91
31 57 54
32 74 48
33 67 11
34 70 78
35 69 66
36 84 8
6 10
laptop 4 7
camera 2 10
xbox 6 6
grinder 4 7
dumbell 2 5
encyclopedia 10 4
6 17
laptop 4 7
camera 2 10
xbox 6 6
grinder 4 7
dumbell 2 5
encyclopedia 10 4
*/