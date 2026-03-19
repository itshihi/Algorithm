#include <iostream>
#include <algorithm>
#include<cstring>
#include <vector>
using namespace std;

int man[21];
int suffix[21];

int N, B;
int MIN = 2e9;
vector<int> mins;

bool cmp(int a, int b) {
	return a > b;
}


void init() {
	mins.clear();
	MIN = 2e9;
	memset(man, 0, sizeof(man));
	memset(suffix, 0, sizeof(suffix));

}

void input() {
	cin >> N >> B;
	for (int i = 0; i < N; i++) {
		cin >> man[i];
	}

	suffix[N] = 0;
	for (int i = N - 1; i >= 0; i--) {
		suffix[i] = suffix[i + 1] + man[i];
	}
	sort(man, man + N, cmp);
}

void dfs(int idx, int sum) {

	if (sum >= B) {
		if (MIN > sum) {
			MIN = sum;
			return ;
		}
		
		return ;
	}

	if (idx == N) {
		
		return ;
	}

	if (sum + suffix[idx] < B) return;
	dfs(idx + 1, sum + man[idx]); // 이번 사람을 쓸 때

	dfs(idx + 1, sum); // 안쓸 때




}


int main() {
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		input();
		dfs(0, 0);

		int ans;
		if (MIN != 2e9) {
			ans= MIN;
		}
		else {
			ans = -1;
		}

		cout << "#" << t << " " << ans - B << "\n";
	}
	

}