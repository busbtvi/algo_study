// https://www.algospot.com/judge/problem/read/BLOCKGAME
#include <iostream>
#include <memory.h>
using namespace std;

char dp[1<<25], board[5][5], temp;
bool blocks[8][2][2] = {
    {{0,0}, {1,1}},
    {{0,1}, {0,1}},
    {{1,0}, {1,0}},
    {{1,1}, {0,0}},
    
    {{0,1}, {1,1}},
    {{1,0}, {1,1}},
    {{1,1}, {0,1}},
    {{1,1}, {1,0}},
};
int board_to_int(){
    int result = 0;
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            result = result<<1 | (board[i][j] == '#');

    // cout << "board to int = " << result << endl;
    return result;
}
bool can_i_put(int bi, int r, int c){
    auto& block = blocks[bi];
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(block[i][j] && board[r+i][c+j]=='#')
                return false;
        }
    }

    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(block[i][j]) board[r+i][c+j] = '#';
        }
    }
    return true;
}
void remove(int bi, int r, int c){
    auto& block = blocks[bi];
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            if(board[r+i][c+j]=='#' && block[i][j])
                board[r+i][c+j] = '.';
        }
    }
}
bool check_game_end(){
    for(int i=0; i<5; i++){  // check horizontal
        for(int j=0; j<4; j++){
            if(board[i][j] == '.' && board[i][j+1] == '.')
                return false;
        }
    }

    for(int i=0; i<4; i++){  // check vertical
        for(int j=0; j<5; j++){
            if(board[i][j] == '.' && board[i+1][j] == '.')
                return false;
        }
    }

    return true;
}
// void print_board(){
//     cout << player << endl;
//     for(int i=0; i<5; i++){
//         for(int j=0; j<5; j++) cout << board[i][j] << ' ';
//         cout << endl;
//     }
//     cout << endl;
// }
bool play_game(){  // return this turn's player win
    // print_board();
    char& result = dp[board_to_int()];
    if(result != -1) return result;

    result = false;
    if(!check_game_end()){
        bool exit = false;
        for(int i=0; i<4 && !exit; i++){
            for(int j=0; j<4 && !exit; j++){
                for(int k=0; k<8 && !exit; k++){
                    if(can_i_put(k, i, j)){
                        bool other_win = play_game();
                        remove(k, i, j);

                        if(!other_win){
                            exit = true;
                            result = true;
                        }
                    }
                }
            }
        }
    }

    return result;
}
void solve(){
    memset(dp, -1, sizeof(dp));
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cin >> board[i][j];
    
    // print_board();
    cout << (play_game() ? "WINNING\n" : "LOSING\n");
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    브루트 포스? 50 * 8^12(최악의 경우: 백지 + 모두 2개짜리 놓기)
        - 불가능
    dp로 풀긴 했는데, dp로 만드는 과정에서 &result를 초기화 하는 부분 까먹어서 좀 해멤
*/