// https://www.acmicpc.net/problem/1107
#include <iostream>
#define OverLimit 5000000
using namespace std;

int main(){
    bool buttons[10] = {1,1,1,1,1, 1,1,1,1,1};
    int n, m, up = OverLimit, down = -OverLimit;

    cin >> n >> m;
    for(int i=0, j; i<m; i++){
        cin >> j;
        buttons[j] = false;
    }

    // n번 부터 위로 올라가면서 가장 가까운 번호 탐색
    for(int i=n, j; i<=999999; i++){
        bool possible = true;
        j = i;
        do{
            if(!buttons[j%10]) possible = false;
            j /= 10;
        }while(j>0 && possible);

        if(j == 0 && possible){
            up = i;
            break;
        } 
    }
    // n번부터 아래로 내려감녀서 가장 가까운 번호 탐색
    for(int i=n, j; i>=0; i--){
        bool possible = true;
        j = i;
        do{
            if(!buttons[j%10]) possible = false;
            j /= 10;
        }while(j>0 && possible);

        if(j == 0 && possible){
            down = i;
            break;
        } 
    }

    // 두가지 경우중 차이가 적은것의 버튼 횟수 계산
    int lessGap = (up-n < n-down) ? up : down;  // 둘의 차이가 같으면 작은 번호로(n=99, up=100, down=98 이면 down이 적게 누름)
    int buttonPress = abs(lessGap - n);
    do{
        buttonPress++;
        lessGap /= 10;
    }while(lessGap > 0);

    // 100번에서 출발하는거랑 비교
    cout << min(abs(n-100), buttonPress);
    return 0;
}