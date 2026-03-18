#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
 
// dfs -> visited 처리 -> groupcnt
int N; // 사람 수
int M; // 관계 수
vector<vector<int>> map;
int visited[101]; // 방문
int groupCnt;
 
void init() {
    memset(visited, 0, sizeof(visited));
    map.clear();
    groupCnt = 0;
}
 
void input() {
    cin >> N >> M;
    map.assign(N+1, vector<int>(0));
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        map[x].push_back(y);
        map[y].push_back(x);
         
    }
}
 
void dfs(int now) {
 
    for (auto next : map[now]) {
        if (visited[next] == 0) {
            visited[next] = 1;
            dfs(next);
        }
    }
}
 
void sol(int t) {
    groupCnt = 0;
    for (int i = 1; i <= N; i++) {
        // 이미 방문한 노드
        if (visited[i] == 1) continue;
        visited[i] = 1;
 
        // 미방문, 연결노드없음
        if (map[i].size() == 0) {
            groupCnt++;
            continue;
        }
 
        dfs(i);
        groupCnt += 1;
    }
 
    for (int i = 1; i <= N; i++) {
        if (visited[i] == 0) {
            groupCnt += 1;
        }
    }
 
    cout << "#" << t << " " << groupCnt << "\n";
}
int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
 
        init();
        input();
        sol(t);
    }
}