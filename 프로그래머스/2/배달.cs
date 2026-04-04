using System;
using static System.Console;
using System.Collections.Generic;


class MinHeap {
    private List<(int node, int cost)> heap = new List<(int node, int cost)>();
    public int Count() {
        return heap.Count;
    }
    
    
    // 맨 아래에 넣고 끌어올리기
    public void Push(int node, int cost) {
        
        heap.Add((node, cost));
        int i = heap.Count-1;
        int parent;
        
        while(i>0) {
            parent = (i-1)/2;
            if(heap[parent].cost <= heap[i].cost) break;
            var tmp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = tmp;
            
            i = parent;
        }
        
    }
    
    // 맨 위에 넣고 내리기
    public (int node, int cost) Pop() {
        var head = heap[0];
        heap[0] = heap[heap.Count-1];
        heap.RemoveAt(heap.Count-1);
        
        int i = 0;
        while(true) {
            int left = i*2 +1;
            int right = i*2+2;
            int smallest = i;
            
            if(left<heap.Count && heap[left].cost < heap[i].cost) {
                smallest = left;
            }
            
            if(right<heap.Count && heap[right].cost < heap[i].cost) {
                smallest = right;
            }
            
            if(i==smallest) break; // 최소힙 조건 만족
            
            // parent인 i와 smallest swap
            var tmp = heap[smallest];
            heap[smallest] = heap[i];
            heap[i] = tmp;
            
            i=smallest;
            
        }
        
        return head;
    }
}


class Edge {
    public int to;
    public int w;
    
    public Edge(int to, int w) {
        this.to = to;
        this.w = w;
    }
}
class Solution
{
    public int[] dist;
    public bool[] visited;
    public int solution(int N, int[,] road, int K)
        

    {
        
        dist = new int[N+1];
        visited = new bool[N+1];
        int answer = 0;

        MinHeap pq = new MinHeap();
        
        for(int i=1; i<N+1; i++) {
            dist[i] = int.MaxValue;
        }
        
        // adj 정리
        List<List<Edge>> adj = new List<List<Edge>>();

        
         
        for(int i=0; i<N+1; i++) {
            adj.Add(new List<Edge>());

        }
        
        for(int j=0; j<road.GetLength(0); j++) {
            // adj[0].Add((1,1));
            // Edge e1 = new Edge(road[j,1], road[j,2]);
            adj[road[j,0]].Add(new Edge(road[j,1], road[j,2])); 
            adj[road[j,1]].Add(new Edge(road[j,0], road[j,2])); 
        }
        
        pq.Push(1, 0);
        dist[1] = 0;
        
        visited[1] = true;
        while(pq.Count()>0) {
            var now = pq.Pop();
            
            if(now.cost > dist[now.node]) continue;
            
            // if(dist[now.node] <= K && !visited[now.node]) {
            //     answer++;
            //     visited[now.node] = true;
            // }

            
            // next
            foreach(var nNode in adj[now.node]) {
                int nCost = dist[now.node] + nNode.w;
                // int nowCnt = now.cnt;
                if(dist[nNode.to]  < nCost) continue; // 지나가는게 손해
                // if(dist[nNode.to] == int.MaxValue) nowCnt++;
                dist[nNode.to] = nCost;
                pq.Push( nNode.to, nCost);
            }
        }
        
        for(int i=1; i<N+1; i++) {
            if(dist[i] <=K) answer++;
        }

        return answer;
    }
}
