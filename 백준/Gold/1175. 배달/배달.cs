
using System;
using System.Collections.Generic;

class Program
{
    static int N, M;
    static char[,] map;
    static (int x, int y) start;
    static List<(int x, int y)> cList = new List<(int x, int y)>();

    // 상하좌우
    static int[] dx = { -1, 1, 0, 0 };
    static int[] dy = { 0, 0, -1, 1 };

    struct State
    {
        public int x, y, dir, mask, dist;

        public State(int x, int y, int dir, int mask, int dist)
        {
            this.x = x;
            this.y = y;
            this.dir = dir;
            this.mask = mask;
            this.dist = dist;
        }
    }

    static int GetMask(int x, int y)
    {
        if (x == cList[0].x && y == cList[0].y) return 1; // 01
        if (x == cList[1].x && y == cList[1].y) return 2; // 10
        return 0;
    }

    static int BFS()
    {
        // dir: 0~3, 시작 전 방향은 4로 처리
        bool[,,,] visited = new bool[N, M, 5, 4];
        Queue<State> q = new Queue<State>();

        q.Enqueue(new State(start.x, start.y, 4, 0, 0));
        visited[start.x, start.y, 4, 0] = true;

        while (q.Count > 0)
        {
            State cur = q.Dequeue();

            if (cur.mask == 3) return cur.dist; // 두 C 모두 방문

            for (int ndir = 0; ndir < 4; ndir++)
            {
                // 같은 방향 연속 이동 불가
                if (cur.dir != 4 && cur.dir == ndir) continue;

                int nx = cur.x + dx[ndir];
                int ny = cur.y + dy[ndir];

                // 범위 밖
                if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
                // 벽
                if (map[nx, ny] == '#') continue;

                int nmask = cur.mask | GetMask(nx, ny);

                if (visited[nx, ny, ndir, nmask]) continue;

                visited[nx, ny, ndir, nmask] = true;
                q.Enqueue(new State(nx, ny, ndir, nmask, cur.dist + 1));
            }
        }

        return -1;
    }

    static void Main()
    {
        string[] input = Console.ReadLine().Split();
        N = int.Parse(input[0]);
        M = int.Parse(input[1]);

        map = new char[N, M];

        for (int i = 0; i < N; i++)
        {
            string line = Console.ReadLine();
            for (int j = 0; j < M; j++)
            {
                map[i, j] = line[j];

                if (map[i, j] == 'S')
                    start = (i, j);
                else if (map[i, j] == 'C')
                    cList.Add((i, j));
            }
        }

        Console.WriteLine(BFS());
    }
}