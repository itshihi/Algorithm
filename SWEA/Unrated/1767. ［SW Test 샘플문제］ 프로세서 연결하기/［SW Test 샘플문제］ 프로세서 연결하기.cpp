#include <iostream>
#include <vector>
#include<cstring>
#include<climits>

using namespace std;

int map[13][13];
int N;

// idx==4 는 cells 연결하지않는다.
int dx[5] = { 0, 1, 0, -1, 0 };
int dy[5] = { 1, 0, -1, 0, 0 };
vector<pair<int, int>> cells; // cell의 좌표 저장
vector<int> totalLine; // idx; 먹은 cell 수, val; 최소 전선 길이


int setLines(pair<int,int> now, int d, int mark) {
	int lines = 0;
	int nx = now.first + dx[d];
	int ny = now.second + dy[d];
	
	
	// 전선을 놓을 수 있는가?
	if (mark != 0) {
		int tx = nx; int ty = ny;
		while (tx >= 0 && tx < N && ty >= 0 && ty < N) {
			if (map[tx][ty] > 0) return -1;
			tx += dx[d]; ty += dy[d];
		}
	}

	while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
		
		map[nx][ny] = mark;

		nx += dx[d]; ny += dy[d];
		lines++;
		
	}


	return lines;
	 
}

void getCells(int idx, int totalLines, int cnt, int targetCnt) {

	if (cnt == targetCnt) {
		// 갱신
		if (totalLine[targetCnt] > totalLines) {
			totalLine[targetCnt] = totalLines;
		}
		return ;
	}
	 // 남은 코어가 없음
	if (idx == cells.size()) {
		return ;
	}

	int x= cells[idx].first;
	int y = cells[idx].second;
;
	
	for (int d = 0; d < 5; d++) {

		// 해당 cell x
		if (d == 4) {
			getCells(idx + 1, totalLines, cnt, targetCnt);
			break;
		}
		
		int len = setLines(cells[idx], d, 2);

		// 해당 방향으로 갈 수 없음
		if (len == -1) {
			continue;

		}


		getCells(idx + 1, totalLines + len, cnt + 1, targetCnt);		

		// 백트래킹-전선 원복
		setLines(cells[idx], d, 0);

	}


}

void solution() {
	
	
	// 몇 개 먹을 건지
	for (int c = 1; c <= cells.size(); c++) {
		getCells(0,0,0,c); //int idx, int totalLines, int cnt, int targetCnt

		
	}
}


int main() {
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {

		cin >> N;
		memset(map, 0, sizeof(map));
		cells.clear(); totalLine.clear();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];

				// 벽에 붙어있지 않은 cell일 때
				if (map[i][j] == 1 && i != 0 && j != 0 && i!=N-1 && j!=N-1) {
					cells.push_back({ i, j });
				}
			}
		}

		totalLine.assign(cells.size()+1, INT_MAX);

		solution();

		cout << "#" << t << " ";
		for (int i = cells.size(); i > 0; i--) {
			if (totalLine[i] != INT_MAX) {
				cout << totalLine[i] << "\n";
				break;
			}
		}
	}



}