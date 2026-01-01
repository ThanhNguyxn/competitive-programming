#include <vector>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;

class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        
        int n = tasks.size();
        int m = workers.size();
        
        // Binary search for the maximum number of tasks k
        int low = 0, high = min(n, m);
        int ans = 0;
        
        while (low <= high) {
            int k = low + (high - low) / 2;
            
            if (check(k, tasks, workers, pills, strength)) {
                ans = k;
                low = k + 1;
            } else {
                high = k - 1;
            }
        }
        
        return ans;
    }
    
    bool check(int k, vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        deque<int> dq;
        int workerIdx = workers.size() - 1; 
        int pillsLeft = pills;
        
        // Iterate through the k smallest tasks from LARGEST to SMALLEST
        for (int i = k - 1; i >= 0; --i) {
            int taskReq = tasks[i];
            
            // Add all workers who can complete this task WITH a pill
            // workers are sorted ascending. We iterate from largest to smallest.
            // We want to maintain the deque sorted such that front is weakest, back is strongest.
            // Since we add from largest workers downwards, and we use push_front,
            // the first added (largest) will be at the back?
            // Wait. 
            // workerIdx starts at end (largest).
            // 1. workerIdx = largest. push_front(largest). dq: [largest]
            // 2. workerIdx = 2nd largest. push_front(2nd largest). dq: [2nd largest, largest]
            // So dq.front() is indeed the WEAKEST among those added. dq.back() is STRONGEST.
            
            while (workerIdx >= (int)workers.size() - k && workers[workerIdx] + strength >= taskReq) {
                dq.push_front(workers[workerIdx]);
                workerIdx--;
            }
            
            if (dq.empty()) return false;
            
            // Greedy Strategy:
            // 1. Try to use the STRONGEST worker (back) WITHOUT a pill.
            //    If they can do it, use them. This saves pills.
            //    (Since we process tasks largest to smallest, if the strongest can do it, 
            //     it's generally safe to use them).
            
            if (dq.back() >= taskReq) {
                dq.pop_back();
            } else {
                // 2. If strongest cannot do it without a pill, then NO ONE can do it without a pill
                //    (because everyone else is weaker).
                //    So we MUST use a pill.
                //    We should use the pill on the WEAKEST eligible worker (front)
                //    to save the stronger workers for potentially harder tasks (or to do tasks without pills).
                
                if (pillsLeft > 0) {
                    pillsLeft--;
                    dq.pop_front();
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};
