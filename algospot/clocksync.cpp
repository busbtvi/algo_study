// https://www.algospot.com/judge/problem/read/CLOCKSYNC
#include <vector>
#include <iostream>
using namespace std;

int current_min;
vector<vector<int>> buttons{
	{0,1,2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};
bool is_all_12(vector<int>& clocks){
	bool all_12 = true;
	for(int i=0; i<16 && all_12; i++)
		all_12 &= (clocks[i] == 0);
	return all_12;
}
void recursive(vector<int>& clocks, int index, int button_press_acc){
	if(is_all_12(clocks)){
		if(button_press_acc < current_min)
			current_min = button_press_acc;
		return;
	}
	if(index == 10 || current_min < button_press_acc) return;

	for(int i=1; i<=4; i++){  // press button 1 to 4(== 0 press) time
		for(int j=0; j<buttons[index].size(); j++)
			clocks[buttons[index][j]] = (clocks[buttons[index][j]] + 3) % 12;
		
		recursive(clocks, index+1, button_press_acc + (i%4));
	}
}
void solve(){
	vector<int> clocks(16);
	for(int i=0, a; i<16; i++){
		cin >> a;
		clocks[i] = (a == 12) ? 0 : a;
	}

	current_min = 40;
	recursive(clocks, 0, 0);
	cout << (current_min == 40 ? -1 : current_min) << endl;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case > 0) {
		solve();
		test_case--;
	}
	return 0;
}

/*
	-- 생각 과정 --
	각 버튼을 4번 누르면 다시 제자리니 최대 3 * 10 번 이내로 버튼을 누를 수 있음
	순서가 상관 있나? x
		- 0번 버튼 부터 1,2,3,4 번 누르고 다음버튼 누르는 방식으로 재귀?
		- 4번 누르는 것은 현재 사이클에서 clocks를 초기화(4번 누르면 다시 원점) 및 버튼을 0번 누른것을 처리

	현재 최소보다 button을 이미 더 눌렀으면 탐색 중지

	-- 생각 못한 부분 --
	경우의 수가 30번이 아니라, 4 ^ 10 = 1,048,576번 걸림
		- 물론 그래도 완전탐색으로 시간내에 풀이 가능
*/