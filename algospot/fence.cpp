// https://www.algospot.com/judge/problem/read/FENCE
#include <iostream>
#include <cassert>
using namespace std;

int n, heights[20000];
int max_area(int beg, int end){
	if(beg+1 == end) return heights[beg];

	// 여기는 range로 접근 [beg, end)
	int mid_index = (beg + end) / 2;
	int left_area = max_area(beg, mid_index);
	int right_area = max_area(mid_index, end);

	// 여기는 index로 사용하기때문에 [to_beg, to_end]
	int to_beg = mid_index-1, to_end = mid_index;
	int mid_min_height = min(heights[to_beg], heights[to_end]);
	int mid_area = mid_min_height * 2;
	while(to_beg > beg || to_end < end-1){  // todo: change condition
		bool move_left = true;
		if(to_beg-1 >= beg && to_end+1 < end){  // both in scope
			// check both end's height
			move_left = (heights[to_beg-1] > heights[to_end+1]);
		} else {  // only one side is in scope
			move_left = (to_beg-1 >= beg);
		}

		if(move_left){
			to_beg--;
			mid_min_height = min(mid_min_height, heights[to_beg]);
		} else {
			to_end++;
			mid_min_height = min(mid_min_height, heights[to_end]);
		}
		mid_area = max(mid_area, mid_min_height * (to_end - to_beg+1));
	}

	return max(max(left_area, right_area), mid_area);
}
void solve(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> heights[i];

	cout << max_area(0, n) << endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	무식하게 가능? -> 불가능
		시작, 끝 뽑기 = N^2
		범위에서 최소 높이 찾기 = N
		총 50번 -> O(N^3) * 50
	슬라이딩 윈도우 방식으로 될꺼 같은데?
		(높이, index) tuple을 높이기준 오름차순 정렬 하는 heap
		음... 어렵네
	챕터가 분할 정복이니
		max(왼쪽 반틈, 오른쪽 반틈, 가운데) -> 가운데를 어떻게 하지?
		가운데 2칸중 낮은 것 * 2를 현재 넓이라고 설정
			좌,우중 더 높은 곳으로 한칸 이동, 기존과 현재의 넓이 비교 -> 양쪽 끝에 도달할 때까지 반복
		O(N * logN) 나올듯?
	
	-- 생각해 볼 것 --
	책 p.201에서 stack + 스위핑으로 선형시간으로 된다고 함
*/