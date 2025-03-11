// https://www.algospot.com/judge/problem/read/MORSE
#include <iostream>
#include <memory.h>
#include <cassert>
using namespace std;

int n, m, k;
int cache[101][101];
// -가 dash개, o가 o개 있을때 생길 수 있는 모든 경우의 수
int recursive(int dash, int o, int curCount){  // dash: [0,m], o: [0,m]
	if(dash == 0 || o == 0){
		cache[dash][o] = 1;
		return 1;
	}

	int& ans = cache[dash][o];
	if(ans == 0){
		ans = recursive(dash-1, o, curCount);

		if(k < curCount + ans) return ans;
		ans += recursive(dash, o-1, curCount + ans);
		cache[o][dash] = ans;  // 조합에서 4C1이나 4C3은 같기때문에
	}
	return ans;
}
void reconstruct(){
	int dash=n, o=m, curCount = 0;
	while(dash > 0 || o > 0){
		if(dash == 0 || o == 0){
			cout << (dash ? '-' : 'o');
			if(dash) dash--;
			else o--;

			continue;
		} 

		if(curCount + cache[dash-1][o] < k){  // 현재를 -로 했는데도, 모자람
			cout << 'o';  // 현재를 o로 설정
			curCount += cache[dash-1][o];
			o--;
		} else {
			cout << '-';
			dash--;
		}
	}
	cout << endl;
}
void solve(){
	memset(cache, 0, sizeof(cache));
	cin >> n >> m >> k;

	recursive(n, m, 0);
	reconstruct();
}
int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	무식하게, 하나씩 세는걸 잠깐 생각해 봤는데, 이진 탐색으로 해도 될듯?
		- 가능한 경우를 미리 다 게산하고, 이진탐색으로 할려고 했는데
		  모든 경우의 수가 100^100 이상이 되어버림...
	o의 갯수, -의 갯수를 받고, 현재의 순서?(정답 출력을 위해)
		cur_count += 현 위치에서 -를 골랐을때, 뒤의 모든 경우(o_count, -_count-1)
		return 현 위치에서 o를 골랐을때, 뒤의 경우(o_count-1, -_count)
	cache[- 갯수][o 갯수]: 남은 -,o를 사용했을때 모든 경우의 수

	모든 경우를 다 계산하면 overflow가 나기때문에, 필요한 부분까지만 계산하고 끊기
	
	-- 생각해 볼 점 --
	답을 역추적 하는 과정이 한번에 생각하기 복잡하기 때문에, 우선 최적해 찾는거에만 집중
	그리고 추가로 답을 역으로 구성하는 방법 생각해보기

	경우의 수가 overflow 되더라도, k = 1,000,000,000 이상은 정확한 값이 필요한게 아니라
	"이것보다 크다"는 사실만 중요하기 때문에 미리 이항계수를 다 구해놓아도 된다
		bino[n][m] = max(1,000,000,000, 실제 값)
	string을 파라미터로 넘겨서 계속 더해가는 것도 좋은 방법
*/