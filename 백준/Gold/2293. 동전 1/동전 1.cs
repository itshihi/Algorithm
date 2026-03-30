using System;
using System.Runtime.InteropServices;
using System.Runtime.Intrinsics.X86;
using static System.Console;


static class Solution
{

    //idx; 동전 총 갯수, val; 경우의 수 집합

    static int[] coins;

    static int k;
    static int n;
    static int answer;
    static int[,] memo; // 총합이 val1일 때 val2 이상의 수만 가용할 경우

    static int dfs(int now, int idx)
    {
        if(now == k)
        {
            return 1;
        }
        if(now > k)
        {
            return 0;
        }
        if (memo[now,idx]!=-1)
        {
            return memo[now, idx];
        }


        int cnt = 0;
        for(int i=idx; i<coins.Count();  i++)
        {
            cnt+=dfs(now + coins[i], i);
        }


        // 최종
        return memo[now, idx] = cnt;

    }

    static void Main()
    {
        var line = ReadLine().Split();
        n = int.Parse(line[0]);
        k = int.Parse(line[1]);
        answer = 0;

        coins = new int[n];
        for (int i = 0; i < n; i++)
        {
            coins[i] = int.Parse(ReadLine());
        }

        memo = new int[k + 1, n];
        for(int i=0; i<=k; i++)
        {
            for(int j=0; j<n; j++)
            {
                memo[i, j] = -1;
            }
        }

        answer = dfs(0, 0);


        Write(answer);


        }


    }
