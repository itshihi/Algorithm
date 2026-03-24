using System;
using System.Collections.Generic;
// 숫자 12를 만드는데 여러 경우의 수가 존재한다 -> 그리디
// top-down(재귀) vs bottom-up(for문, forward/backward)

public class Solution {
    public int solution(int N, int number) {
        int answer = 0; // N 사용 횟수
        List<HashSet<int>> dp = new List<HashSet<int>>(); // idx; N 사용횟수, 만들 수 있는 숫자 집합
        
        // dp[i] = dp[i-1] 사칙연산 dp[i-2]
        // ex N=1인 경우 dp[0] = 0, dp[1]={1}, dp[2] ={1, 11}
        // dp[3] = 1+1, 1-1, 1*1, 1/1, 11+1, 11-1, 11*1, 11/1, 111
        //       = {0, 1, 2, 10, 11, 12, 111}
        
        // 언제 체크해야하지? 
        
        for(int i=0; i<=8; i++) {
            dp.Add(new HashSet<int>());
        }
//         dp[0].Add(0);
        // dp[1].Add(N);
        
//         dp[2].Add(N*10+N);
//         dp[2].Add(N+N);
//         dp[2].Add(N*N);
//         dp[2].Add(N/N);
        
        for(int i=1; i<=8; i++) { // 추가 대상
            
            //NN..꼴의 숫자 추가
            int tmp=0;
            for(int k=0; k<i; k++) {
                tmp = tmp*10+N;
            }            
            dp[i].Add(tmp);
            
            for(int j=1; j<i; j++) {
                foreach(var b in dp[j]) {
                    foreach(var bb in dp[i-j]) {
                        int x, y;
                        if(b>bb) {
                            x=b; y=bb;
                        } else {
                            x=bb; y=b;
                        }
                        
                        dp[i].Add(x+y);
                        dp[i].Add(x-y);
                        dp[i].Add(x*y);
                        if(y==0) continue;
                        
                        dp[i].Add(x/y);
                    }
                }
                
                
            }
            
            
            
            foreach(var v in dp[i]) {
                if(v==number) return i;
            }
        }
        
       
        
        return -1;
    }
}