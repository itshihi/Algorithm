#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;


int N;
int nums[10];
int remain = 0;
int total;
int memo[1<<9][9001];
int fact[10];


void input() {
	remain = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> nums[i];
		remain += nums[i];
	}
}

int countBit(long long mask) {
	int cnt = 0;
	while (mask) {
		cnt += (mask & 1);
		mask >>= 1; 
	}

	return cnt;
}

void dfs(int mask, int diff, int remain) {
	// 모두 방문함
	if (mask == (1 << N) - 1) {
		
		total++;
		return;
	}

	if (memo[mask][diff]!=-1) {
		total += memo[mask][diff];
		return;
	}

	long long before = total;


	// remain+rs<=ls == remain - (ls-rs) <= 0
	if (remain - diff <= 0) {
		int cnt = countBit(mask);
		int falsecnt = N - cnt;
		memo[mask][diff] = fact[falsecnt] * (1<<falsecnt);
		
		total += memo[mask][diff];
		return;
	}

	for (int i = 0; i < N; i++) {
		int now = nums[i];
		if (mask & (1 << i)) continue;
		
		// visited 처리
		int nmask = mask | 1 << i;

		// remain 처리
		int nremain = remain - now;

		if (now <= diff) { // 오른쪽 넣기
			dfs(nmask, diff-now, nremain);
		}

		// 왼쪽 넣기

		dfs(nmask, now + diff, nremain);
	
	}

	// 모든 자식 상태를 다 보고 난 뒤
	memo[mask][diff] = total - before;



}


int main() {
	int T; cin >> T;

	for (int i = 0; i < 10; i++) {
		int val = 1;
		for (int j = 1; j <= i; j++) {
			val *= j;
		}
		fact[i] = val;
	}

	for (int t = 1; t <= T; t++) {
		total = 0;
		input();
		sort(nums, nums + N, greater<int>());
		memset(memo, -1, sizeof(memo));

		
		dfs(0, 0, remain);

		cout << "#" << t << " " << total << "\n";

	}
}
