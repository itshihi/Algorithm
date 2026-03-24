#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    
    vector<vector<int>> memo;
    int len = triangle.size();
    cout << len;


    memo.assign(len, vector<int>(len,0));
    memo[0][0] = triangle[0][0];
    
    for(int i=1; i<len; i++) {
        for(int j=0; j<=i; j++) {
            if(j==0) {
                memo[i][j] =memo[i-1][j] + triangle[i][j];
                continue;
            }
            if(j==i) {
                memo[i][j] =memo[i-1][j-1] + triangle[i][j];
                continue;
            }
            
            memo[i][j] = max(memo[i-1][j-1], memo[i-1][j]) + triangle[i][j];
        }
    }
    
    answer = *max_element(memo[len-1].begin(), memo[len-1].end());
    return answer;
}