// https://www.acmicpc.net/problem/11758
#include <iostream>
using namespace std;

int main(){
    int p[3][2], ans;

    for(int i=0; i<3; i++)
        cin >> p[i][0] >> p[i][1];

    ans = (p[1][0]-p[0][0])*(p[2][1]-p[1][1]) - (p[1][1]-p[0][1])*(p[2][0]-p[1][0]);
    // cout << ans << '\n';
    cout << ((ans == 0) ? 0 : (ans > 0) ? 1 : -1);
    return 0;
}