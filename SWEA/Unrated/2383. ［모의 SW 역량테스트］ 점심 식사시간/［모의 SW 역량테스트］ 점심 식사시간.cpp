#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int map[11][11];
vector<pair<int, int>> people; // idx; 사람번호, val; 초기좌표

struct Stair {
	int x;
	int y;
	int k;
};
vector<Stair> stairs; //idx; 계단번호, val; 좌표, 내려가는 시간K

int target[11];
int minTime = 2e9;


void init() {
	people.clear();
	stairs.clear();
	memset(target, 0, sizeof(target));
	minTime = 2e9;

}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				people.push_back({ i,j });
			}
			else if (map[i][j] > 1) {
				stairs.push_back({ i, j, map[i][j] });
			}

		}
	}
}



int getDistance(pair<int, int> a, pair<int, int> b) {
	return abs(a.first-b.first) + abs(a.second-b.second);
}

int simulation() {

	// 계단 1에 올라가는 사람들의 이동거리
	vector<int> s1;
	vector<int> s2;

	for (int p = 0; p < people.size(); p++) {
		if (target[p] == 0) s1.push_back(getDistance(people[p], { stairs[0].x, stairs[0].y }));
		if( target[p] == 1) s2.push_back(getDistance(people[p], { stairs[1].x, stairs[1].y }));
	}
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	// 계단1을 다 처리한다.

	vector<int> board1;
	for (int i = 0; i < s1.size(); i++) {

		int arrived = s1[i];
		board1.erase(
			remove_if(board1.begin(), board1.end(), [arrived](int f) {return f <= arrived+1; }),
			board1.end()
		);



		if (board1.size() < 3) { // 자리 있음
			int arrivalTime = s1[i]+1;
			board1.push_back(arrivalTime + stairs[0].k);  
		}
		else { // 자리없음
			sort(board1.begin(), board1.end());
			int wait = board1[0]; // 제일 먼저 나갈 애
			board1.erase(board1.begin());

			int arrivalTime = max(s1[i]+1, wait) ; // 이동시간 vs 대기시간
			board1.push_back(arrivalTime + stairs[0].k);
		}
	}


	// 계단2을 다 처리한다.
	vector<int> board2;
	for (int i = 0; i < s2.size(); i++) {

		int arrived = s2[i]+1;
		board2.erase(
			remove_if(board2.begin(), board2.end(), [arrived](int f) {return f <= arrived+1; }),
			board2.end()
		);
		


		if (board2.size() < 3) {
			board2.push_back(s2[i]+stairs[1].k + 1);
		}
		else {
			sort(board2.begin(), board2.end());

			int wait = board2[0];
			board2.erase(board2.begin());
			int arrivalTime = max(s2[i] + 1, wait);
			board2.push_back(arrivalTime + stairs[1].k);
		}

	}

	int s1Max=0;  int s2Max=0;
	if (!s1.empty()) {
		s1Max = *max_element(board1.begin(), board1.end());;
	}
	if (!s2.empty()) {
		s2Max = *max_element(board2.begin(), board2.end());
	}
	
	return max(s1Max, s2Max);


}

void dfs(int nowP) {
	
	// 기저1; 모든 사람을 다 봄
	if (nowP == people.size()) {
		int time = simulation();
		minTime = min(minTime, time);
		return;
	} 

	target[nowP] = 0;
	dfs(nowP + 1);

	target[nowP] = 1;
	dfs(nowP+1);
}

int main() {
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		input();
		dfs(0);
		//dfs(0, 1);
		cout <<"#" << t << " " << minTime << "\n";

	}

}