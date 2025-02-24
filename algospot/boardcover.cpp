// https://www.algospot.com/judge/problem/read/BOARDCOVER
#include <iostream>
using namespace std;

int w,h;
int recursion(bool white[20][20], int r, int c){
    // cout << "r = " << r << ", c = " << c << endl;
    // for(int i=0; i<h; i++){
    //     for(int j=0; j<w; j++) cout << white[i][j] << ' ';
    //     cout << endl;
    // }
    // cout << endl;

    if(w <= c){
        if(white[r][w-1]) return 0;  // current line is not fully filled

        if(r < h-2) return recursion(white, r+1, 0);  // can move to next line
        else {  // next line is last line
            bool lastline_all_black = true;  // check last line is all black
            for(int j=0; j<w && lastline_all_black; j++)
                lastline_all_black &= !white[h-1][j];
            
            return lastline_all_black ? 1 : 0;
        }
    }

    int possilbe_case = 0;
    if(white[r][c]){
        bool atleast_one_possilbe = false;
        if(white[r+1][c] && white[r+1][c+1]){
            white[r  ][c  ] = false;
            white[r+1][c  ] = false;
            white[r+1][c+1] = false;
            possilbe_case += recursion(white, r, c+1);
            white[r  ][c  ] = true;
            white[r+1][c  ] = true;
            white[r+1][c+1] = true;

            atleast_one_possilbe = true;
        }
        if(white[r+1][c] && white[r][c+1]){
            white[r  ][c  ] = false;
            white[r+1][c  ] = false;
            white[r  ][c+1] = false;
            possilbe_case += recursion(white, r, c+1);
            white[r  ][c  ] = true;
            white[r+1][c  ] = true;
            white[r  ][c+1] = true;

            atleast_one_possilbe = true;
        }
        if(white[r][c+1] && white[r+1][c+1]){
            white[r  ][c  ] = false;
            white[r  ][c+1] = false;
            white[r+1][c+1] = false;
            possilbe_case += recursion(white, r, c+2);
            white[r  ][c  ] = true;
            white[r  ][c+1] = true;
            white[r+1][c+1] = true;

            atleast_one_possilbe = true;
        }
        if(white[r+1][c] && c>0 && white[r+1][c-1]){
            white[r  ][c  ] = false;
            white[r+1][c  ] = false;
            white[r+1][c-1] = false;
            possilbe_case += recursion(white, r, c+1);
            white[r  ][c  ] = true;
            white[r+1][c  ] = true;
            white[r+1][c-1] = true;
            
            atleast_one_possilbe = true;
        }

        if(!atleast_one_possilbe) return 0;
    } else possilbe_case += recursion(white, r, c+1);

    return possilbe_case;
}

int solve(){
    bool board[20][20] = {0, };
    char tile_color;
    cin >> h >> w;
    
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++){
            cin >> tile_color;
            board[i][j] = (tile_color == '.');
        }
        
    return recursion(board, 0, 0);
}

int main(){
    int test_case;
    cin >> test_case;

    while(test_case > 0){
        cout << solve() << endl;
        test_case--;
    }

    return 0;
}

/*
    -- 생각 과정 --
    브루투포스로 풀 수 있나? 4(타일을 돌리는 경우) ^ 17(50개 / 3) * 30(test case)
        안될 꺼 같은데... 다른 방법이 생각이 안나네
    왼쪽 위에서 부터 오른쪽 아래로 내려오며 하나씩 채우는 재귀
    + 불가능한 경우 탈출(위에서 부터 채우기 때문에 현재 줄에 흰색이 남아있으면 안됨)

    음... 모르겠음
    음... 맞게 생각했는데, 그냥 구현 이슈

    -- 생각 못한 부분 --
    경우의 수는 굉장히 큰게 맞는데, 모두 흰색인 2*3을 생각해보면 경우의 수는 4(회전 방향)^2(타일 수)
    인데 실제로는 2가지 밖에 없음

    -- 잘못 구현한 부분 --
    현재 타일이 흰색이면 다음의 3가지 경우의 타일을(현재 타일을 검은색으로 바꾸는 타일)
    .   ..  ..
    ..  .    .
    현재가 검은 색이면 다음의 타일(현재 타일은 그대로 두는 경우)
     .
    ..
    이렇게 생각을 하고 구현을 했는데, 제한되는 경우가 발생(예제의 2번째 3 * 7)
        -> 그냥 처음부터 가장 왼쪽 위에서 부터 차례로 `흰색`만 채우면서 내려오는 방식으로
*/