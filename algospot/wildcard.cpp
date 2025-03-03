// https://www.algospot.com/search/?q=wildcard
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

/*
bool is_match(string query, string file){
	bool visited[101][101] = {false,};
	queue<pair<int,int>> q;  // query_index, file_index

	q.push(make_pair(0,0));
	visited[0][0] = true;
	while(!q.empty()){
		auto cur = q.front();
		q.pop();

		if(cur.first == query.size() && cur.second == file.size()) return true;
		if(cur.first < query.size() && cur.second < file.size()){
			if(query[cur.first] == '?' || query[cur.first] == file[cur.second]){
				if(!visited[cur.first + 1][cur.second + 1]){
					visited[cur.first + 1][cur.second + 1] = true;
					q.push(make_pair(cur.first + 1, cur.second + 1));
				}
			} else if(query[cur.first] == '*'){
				for(int i=cur.second; i<=file.size(); i++){
					if(!visited[cur.first + 1][i]){
						visited[cur.first + 1][i] = true;
						q.push(make_pair(cur.first + 1, i));
					}
				}
			}
		} else if(cur.first < query.size()){  // cur.second == file.size
			if(query[cur.first] == '*'){  // but if query have more *
				if(!visited[cur.first + 1][cur.second]){
					visited[cur.first + 1][cur.second] = true;
					q.push(make_pair(cur.first + 1, cur.second));
				}
			}
		}
	}

	return false;
}
*/

string query, file_name;
bool recursive(int query_i, int file_i){
	if(query_i == query.size() && file_i == file_name.size()) return true;
	if(query_i < query.size() && file_i < file_name.size() && 
		(query[query_i] == '?' || query[query_i] == file_name[file_i]))
		return recursive(query_i + 1, file_i + 1);
	
	if(query[query_i] == '*'){
		bool match_succed = false;
		for(int i=file_i; i<=file_name.size() && !match_succed; i++){
			match_succed = recursive(query_i + 1, i);
		}

		return match_succed;
	}
	/*
		query_i == query.size() && file_i < file_name.size()			=> ignore
		query_i < query.size() && file_i == file_name.size()
				only if(query[query_i] == '*')							=> check
		
	*/
	return false;
}
void solve(){
	// string query, file_name;
	vector<string> ans;
	int file_number;

	cin >> query >> file_number;
	for(int i=0; i<file_number; i++){
		cin >> file_name;
		if(recursive(0,0)) ans.push_back(file_name);
		// if(is_match(query, file_name)) ans.push_back(file_name);
	}

	sort(ans.begin(), ans.end());
	for(auto& a: ans) cout << a << endl;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	무식하게 풀기: *가 들어가는 문자열(최악의 경우 ***...a)은
		첫 *가 0 ~ 100(문자열의 최대길이)개의 문자를 대체하는 경우
		두번째 *가 0 ~ 99개를 대체하는 경우
		-> 100! 만큼의 경우가 생김(불가능)
	isMatch[와일드카드 길이][탐색 문자열 길이]로 하면 10,000가지 경우
		-> 긴 하지만, 그냥 bfs로 풀어도 될듯?
*/