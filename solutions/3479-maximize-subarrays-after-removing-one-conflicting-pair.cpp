class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        vector<vector<pair<int,int>>> pairsByMax(n + 2);
        
        for (int i = 0; i < conflictingPairs.size(); i++) {
            int a = conflictingPairs[i][0], b = conflictingPairs[i][1];
            if (a > b) swap(a, b);
            pairsByMax[b].push_back({a, i});
        }
        
        int m = conflictingPairs.size();
        vector<long long> gain(m, 0);
        
        long long baseCount = 0;
        int best1 = 0, best2 = 0;
        int best1Idx = -1;
        
        for (int r = 1; r <= n; r++) {
            for (auto& [a, idx] : pairsByMax[r]) {
                if (a > best1) {
                    best2 = best1;
                    best1 = a;
                    best1Idx = idx;
                } else if (a > best2) {
                    best2 = a;
                }
            }
            
            baseCount += (r - best1);
            
            if (best1Idx >= 0) {
                gain[best1Idx] += (best1 - best2);
            }
        }
        
        long long maxGain = 0;
        for (int i = 0; i < m; i++) {
            maxGain = max(maxGain, gain[i]);
        }
        
        return baseCount + maxGain;
    }
};
