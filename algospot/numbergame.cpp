// https://www.algospot.com/judge/problem/read/NUMBERGAME
#include <iostream>
#include <memory.h>
#define NOTNUMBER 123456789
using namespace std;

int board[50], dp[51][51];
int run_game(int beg, int end){  // [beg, end)
    if(beg == end) return 0;

    int& ans = dp[beg][end];
    if(dp[beg][end] == NOTNUMBER){
        ans = board[beg] - run_game(beg+1, end);
        ans = max(ans, board[end-1] - run_game(beg, end-1));

        if(end - beg >= 2){
            ans = max(ans, -run_game(beg+2, end));
            ans = max(ans, -run_game(beg, end-2));
        }        
    }
    return ans;
}
void solve(){
    for(int i=0; i<51; i++)
        for(int j=0; j<51; j++) dp[i][j] = NOTNUMBER;

    int n;
    cin >> n;
    for(int i=0; i<n; i++) cin >> board[i];

    cout << run_game(0, n) << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    tictactoe와 비슷하게, 현재 보드 상태(beg, end)를 받고
    몇점차이로 이기는지를 반환
    dp 테이블 범위 조심하기    -> 한번 틀림
*/