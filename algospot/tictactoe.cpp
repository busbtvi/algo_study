// https://www.algospot.com/judge/problem/read/TICTACTOE
#include <iostream>
#include <memory.h>
using namespace std;

char board[3][3];
char someone_win(){
    for(int i=0; i<3; i++)
        if(board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    for(int j=0; j<3; j++)
        if(board[0][j] != '.' && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            return board[0][j];
    if(board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[1][1];
    if(board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[1][1];
    return '.';  // 아직 승패 안남
}
bool board_full(){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] == '.') return false;
    return true;
}
int can_win(char turn){  // -1(turn loose), 0(tie), 1(turn win)
    char winner = someone_win();
    if(winner != '.') return turn == winner ? 1 : -1;
    if(board_full()) return 0;

    int result = -1;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++){
            if(board[i][j] == '.'){
                board[i][j] = turn;
                int enemy_result = can_win((turn == 'x' ? 'o' : 'x'));
                board[i][j] = '.';

                if(enemy_result == -1) return 1;  // 한 경우라도 상대가 지면, 내가 이김
                if(enemy_result == 0) result = 0;  // 한 경우라도 상대랑 비기면, 최소 비김
            }
        }
    
    return result;
}
void solve(){
    int x_count = 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++){
            cin >> board[i][j];

            if(board[i][j] == 'x') x_count++;
            if(board[i][j] == 'o') x_count--;
        }
    
    char start = (x_count == 0) ? 'x' : 'o';
    int result = can_win(start);

    if(result == 1) cout << start << endl;
    else if (result == -1) cout << ((start == 'x') ? 'o' : 'x') << endl;
    else cout << "TIE" << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    '내가 이길 수 있는지'(혹은 비길지)를 반환하는 함수
    완전 탐색으로 모든 경우
        내가 이김 == 내 선택 중 하나이상이 상대의 패배
*/