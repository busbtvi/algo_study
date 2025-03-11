// https://www.algospot.com/judge/problem/read/NUMB3RS
#include <iostream>
#include <cassert>
#include <memory.h>
#include <iomanip>
using namespace std;

int village, day, p, path[50][50], t;
int total_path[50];  // 한 마을에서 다른 마을로 갈 수 있는 총 경우
double probability[100][50] = {0.0 };  // [day][villiage_num]
void calc(){
	for(int i=0; i<100; i++)
		for(int j=0; j<50; j++) probability[i][j] = 0;

	// day 0
	for(int cur=0; cur<village; cur++){
		if(p == cur) probability[0][cur] = 0;
		if(path[p][cur]){
			assert(total_path[p] != 0);
			probability[0][cur] = static_cast<double>(1) / total_path[p];
		}
	}

	// day 1 ~ day-1
	for(int i=1; i<day; i++){
		for(int cur=0; cur<village; cur++){
			for(int pre=0; pre<village; pre++){
				if(path[cur][pre]){
					assert(total_path[pre] != 0);
					probability[i][cur] += probability[i-1][pre] / total_path[pre];
				}
			}
		}
	}
	// for(int j=0; j<village; j++) cout << probability[0][j] << ' ';
	// cout << endl;
}
void solve(){
	memset(total_path, 0, sizeof(total_path));

	cin >> village >> day >> p;
	for(int i=0; i<village; i++)
		for(int j=0; j<village; j++){
			cin >> path[i][j];
			
			if(path[i][j]) total_path[i]++;
		}
	
	int outputs[50];
	cin >> t;
	for(int i=0; i<t; i++) cin >> outputs[i];

	calc();
	cout << std::setprecision(8);
	for(int i=0; i<t; i++) cout << probability[day-1][outputs[i]] << ' ';
	cout << endl;
	
	// for(int i=0; i<day; i++){
	// 	for(int j=0; j<village; j++) cout << probability[i][j] << ' ';
	// 	cout << endl;
	// }
	// cout << endl;
}
int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	만약 최악의 경우, 모든 마을이 연결 되어있다면 경우의 수는?
		99^99... - 경우의 수를 먼저 구해서 확률을 계산하기는 불가능
	미리 확률을 구해놓는 다면? probabillity[day][마을 번호]
		- N^3 * 100일
	
	-- 생각해 볼 것 --
	재귀로 다시 풀어보기, 재귀로 뒤에서 부터 풀어보기
*/