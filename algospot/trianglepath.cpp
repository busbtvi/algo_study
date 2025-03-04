// https://www.algospot.com/judge/problem/read/TRIANGLEPATH
#include <iostream>
#include <cassert>
using namespace std;

void solve(){
	int nums[100][100] = {0,}, maxs[100][100] = {0,};
	int n, ans = 0;
	cin >> n;

	for(int i=0; i<n; i++){
		for(int j=0; j<i+1; j++) cin >> nums[i][j];

		if(i == 0) maxs[0][0] = nums[0][0];
		else {
			maxs[i][0] = nums[i][0] + maxs[i-1][0];
			for(int j=1; j<i+1; j++){  // check j range
				maxs[i][j] = max(maxs[i-1][j], maxs[i-1][j-1]) + nums[i][j];
			}
		}
	}

	for(int j=0; j<n; j++) ans = max(ans, maxs[n-1][j]);
	cout << ans << endl;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	완전 탐색을 잠깐 생각했으나, max를 활용하는 방식이 바로 생각남

	-- 생각해 볼 것 --
	재귀 함수를 pathSum(x, y, sum) 이전까지의 최대합이 sum이고 현재 위치가 x,y 일 때
	총 경로의 최대값을 반환하게 작성했다면, memoization을 x,y,sum으로 이루어저야 함
	하지만 sum은 이미 해결한 부분이고, x,y는 해결하지 못한 부분이기 때문에 같이 묶는것은 비효율적

	이미 해결한 부분과, 해결하지 못한 부분문제를 엮을 필요 없다.
	최적 부분 구조: 각 부분 문제의 최적해로, 전체 문제를 풀 수 있다
*/