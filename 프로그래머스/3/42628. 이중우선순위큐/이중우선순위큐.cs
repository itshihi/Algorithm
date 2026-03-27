using System;
using System.Collections.Generic;
using static System.Console;

public class Solution {
    
    public int[] solution(string[] operations) {
        var pq = new SortedSet<int>();

        int[] answer = new int[2]; 
        
        foreach(var line in operations) {
           var order = line.Split();
            
            if(order[0] == "I") {
                pq.Add(int.Parse(order[1]));
                continue;
            }
            
            if(order[0] == "D") {
                if(pq.Count != 0) {
                    
                    if(order[1] == "1") {
                    pq.Remove(pq.Max);
                    
                    } else {
                        pq.Remove(pq.Min);
                    }
                    
                }
                
            }
        }
        
        if(pq.Count == 0){
            answer[0] = 0;
            answer[1] = 0;
            
        } else {
            answer[0] = pq.Max;
            answer[1] = pq.Min;
        }
        
        
        
        return answer;
    }
}