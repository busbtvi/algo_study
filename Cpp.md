# 헷갈리는 문법

- pattern matching

  ```cpp
      using intp = pair<int, int>;
      priority_queue<intp, vector<intp>, greater<intp>> q;
      priority_queue<intp, vector<intp>, less<intp>> q;
      auto [time, loc] = q.top();
  ```

- custom compareator

  ```cpp
  auto comp = [](const intp& a, const intp& b){};
  priority_queue<intp, vector<intp>, decltype(comp)> hacking(comp);

  sort(contry, contry + n, [](const ilpair& a, const ilpair& b) -> bool {
        return a.second > b.second;
    });


  class Cmp {
    public: bool operator()(const intp& a, const intp& b){}
  };
  priority_queue<intp, vector<intp>, Cmp> q;
  ```

- map

  ```cpp
  #include <map>
  map<string, int> m;

  if(m.find("") != m.end())
  m["key"] = value;
  m.clear();
  ```

  - unordered_map: map보다 빠르나 정렬 X

# 간혹 쓰이는 알고리즘

- 위상 정렬: 진입 차수가 0인 노드를 q에 넣어서 시작. q에서 원소를 빼서 해당 노드의 진출 차수를 없애고, 새로 진입차수가 0인 노드를 q에 넣음
  - [read](https://velog.io/@kimdukbae/%EC%9C%84%EC%83%81-%EC%A0%95%EB%A0%AC-Topological-Sorting)
