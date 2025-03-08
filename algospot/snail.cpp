// https://www.algospot.com/judge/problem/read/SNAIL
#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

double probability[1001][1001];
double recursive(int day, int len){  // day: []
    if((day == 0.0 && len != 0.0) || (day * 2 < len)) return 0;
    if(len <= day || len == 0) return 1.0;

    double& ans = probability[day][len];
    if(ans != 0.0) return ans;

    ans = recursive(day-1, len-2) * 0.75 + recursive(day-1, len-1) * 0.25;
    return ans;
}
void solve(){
    int depth, day;
    cin >> depth >> day;

    for(int i=0; i<=day; i++)
        for(int j=0; j<=depth; j++) probability[i][j] = 0.0;
    cout << std::setprecision(10) << recursive(day, depth) << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    확률[남을 날짜][남은 거리]: 남은 날짜동안 남은 거리 이상을 올라갈 수 있는 확률
        확률[남은 날짜][남은 거리] = 0.75 * 확률[남은 날짜-1][거리-2] + 0.25 * 확률[남은 날짜-1][남은 거리-1]
*/