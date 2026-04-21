#include <iostream>
#include <vector>
#include <cstring>
#include<climits>
using namespace std;
 
int N;
int map[17][17];
vector<bool> visited;
int minSum = INT_MAX;
 
int checkMin(int amask) {
    vector<int> aidx;
    vector<int> bidx;
    int m = 0;
    int asum = 0;
    int bsum = 0;
 
    while (m < N) {
        if ((bool)(amask & (1 << m)) == 1) {
            aidx.push_back(m);
        }
        else {
            bidx.push_back(m);
        }
        m++;
    }
 
    // asum 구하기
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j <N/2; j++) {
            if (i == j) continue;
            asum += map[aidx[i]][aidx[j]];
            bsum += map[bidx[i]][bidx[j]];
        }
    }
 
 
    return abs(asum - bsum);
 
}
 
void dfs(int idx, int amask, int cnt) {
     
    if (cnt == N / 2) {
 
        int tmp = checkMin(amask);
         
        // 최솟값 비교
        if (minSum > tmp) {
            minSum = tmp;
        }
 
        return ;
    }
 
    int nmask = amask; // 복사본
 
    for (int i = idx; i < N; i++) {
        // 아직 안먹었는지 확인
        if (nmask & (1 << i)) continue;
 
        nmask = amask;
 
        // 안먹었다면 먹는다.
        nmask |= (1 << i);
 
        // dfs
        dfs(i + 1, nmask, cnt + 1);
 
    }
}
 
 
 
int main() {
 
    cin.tie(NULL);
    ios::sync_with_stdio(false);
 
    int T;
    cin >> T;
 
    for (int t = 1; t <= T; t++) {
        N = 0;
        memset(map, 0, sizeof(map));
        minSum = INT_MAX;
 
        cin >> N;
 
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                cin >> map[r][c];
            }
        }
 
        // a가 무조건 0을 먹는다.
        dfs(1, 1, 1);
 
 
        cout << "#" << t << " " << minSum << "\n";
    }
 
}
