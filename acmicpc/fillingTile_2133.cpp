// https://www.acmicpc.net/problem/2133
#include <iostream>
using namespace std;

/*
    홀수는 3*홀수는 2*1 타일로 채울 수 없음
    dp 방식으로 생각(이전 n-2에 2칸이 더 생김)

    뒤에 새로 생기는 2칸이 독립적일 경우 (dp[n-2] * 3)
    뒤에 새로 생기는 칸이 이전과 연결 되어 있을 경우
        dp[n-4] * 2가지(아래처럼 연결 되어있는 경우 2가지 밖에 안나옴)
        | - - |     - - - -
        | - - |     | - - |
        - - - -     | - - |
*/
int main(){
    int n, tiles[31] = {1,0,3,};
    cin >> n;

    for(int i=3; i<=n; i++){
        if(i%2 == 1) continue;

        for(int j=2; j<=i; j+=2)
            tiles[i] += tiles[i-j] * ((j==2) ? 3 : 2);
    }

    cout << tiles[n];
    return 0;
}