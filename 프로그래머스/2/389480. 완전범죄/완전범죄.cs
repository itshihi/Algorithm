using System;
using static System.Console;

public class Solution {
    
    static int N;
    static int M;
    static int[,] infos=new int[40, 2];
    static int[,,] memo;
    static int len;
    
    static int Dfs(int idx, int sumA, int sumB) {
        
        // 기저
        if(sumA >= N || sumB >= M) return int.MaxValue;
        if(idx == len) return sumA;
        
        if(memo[idx, sumA, sumB]!=-1) return memo[idx, sumA, sumB];
        
        int res = int.MaxValue;
        
        // 재귀
        int tryA = Dfs(idx+1, sumA + infos[idx, 0], sumB);
        if(tryA != int.MaxValue) res= Math.Min(res, tryA);
        
        int tryB = Dfs(idx+1, sumA, sumB+infos[idx, 1]);
        if(tryB  != int.MaxValue) res= Math.Min(res, tryB);
        
        memo[idx, sumA, sumB] = res;
        return res;
    }
    
    
    
    public int solution(int[,] info, int n, int m) {
        
        N=n; M=m; infos=info;
        len = info.GetLength(0);
        
        memo = new int[len, N, M];
        
        
        // memo 값 -1로 초기화
        for(int i=0; i<len; i++) {
            for(int j=0; j<N; j++) {
                for(int k=0; k<M; k++) {
                    memo[i, j, k] = -1;
                }
            }
        }
        
        int ans = Dfs(0, 0, 0);
        return ans==int.MaxValue ? -1 : ans;
    }
}