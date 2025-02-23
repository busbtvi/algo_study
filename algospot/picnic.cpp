// https://www.algospot.com/judge/problem/read/PICNIC
#include <iostream>
using namespace std;

int student_num, match_num;
int find_match(bool is_friend[][10], bool matched[], int beg, int cur_matched){
    while(matched[beg]) beg++;
    int possible_case = 0;

    for(int cur=beg+1; cur<student_num; cur++){
        if(!matched[cur] && is_friend[beg][cur]){
            if(cur_matched+2 == student_num) return 1;

            cur_matched += 2;
            matched[cur] = true;
            possible_case += find_match(is_friend, matched, beg+1, cur_matched);
            matched[cur] = false;
            cur_matched -= 2;
        }
    }

    return possible_case;
}

int solve(){
    bool matched[10] = {0,};
    bool is_friends[10][10] = {0,};

    cin >> student_num >> match_num;
    for(int i=0,a,b; i<match_num; i++){
        cin >> a >> b;
        is_friends[a][b] = true;
        is_friends[b][a] = true;
    }
    
    return find_match(is_friends, matched, 0, 0);
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
    -- 내가 생각한 것 --
    일단은 무식하게
    무식하게 해도 50 * n^2(완전탐색) 되는것 같음
    앞에서 부터 짝을 뒤로 찾아나가기

    -- 잘못 생각한 부분 --
    10명이 모두 친구인 경우, 짝을 지을 수 있는 경우의 수가 
        9 * 7 * 5 * 3 = 945가지 경우
    n^2으로 100가지로 생각했는데 그게 아니었음

    모든 경우의 수를 세면 (0,1), (1,0) 처럼 중복이 생기는데
    `특졍 형태만 세기` 내가 푼 케이스에서는
    `무조건 앞쪽 사람부터 짝을 찾아나가기`로 알지도 못한채 중복을 없애버렸음
*/