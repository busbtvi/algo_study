// https://www.algospot.com/judge/problem/read/POLY
#include <iostream>
#include <cassert>
#include <memory.h>
#define MOD 10000000
using namespace std;

int cache[101][101];
int recursive(int cur, int remain){  // cur: [0, n], remain: [0, n]
	if(remain == 0) return 1;
	if(remain == 1) return cur;
	
	int& ans = cache[cur][remain];
	if(ans == 0){
		for(int next=1; next<=remain; next++){
			if(cur == 0) ans += recursive(next, remain - next);
			else 
				ans += ((cur + next - 1) * recursive(next, remain - next)) % MOD;

			ans = ans % MOD;
		}
	}
	return ans;
}
void solve(){
	memset(cache, 0, sizeof(cache));
	int n, ans;
	cin >> n;

	cout << recursive(0, n) << endl;
}
int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	n 처럼 생긴 모양은 세로 단조 폴리오미노가 아니다. 그럼 가로로 아래에서 부터 쌓아 나가는
	방식으로 생각하면 될꺼 같다.
	각 층이 쌓일 수 있는 경우의 수는, 현재 층 갯수 + 다음층 갯수 - 1 인듯?
		위/아래 의 형식에서: 3/3은 5가지, 3/1은 3가지, 2/3은 4가지
	recursive(현재 층 타일 갯수, 남은 타일 갯수)
*/