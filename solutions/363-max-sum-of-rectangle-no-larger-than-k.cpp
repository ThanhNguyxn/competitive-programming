class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int result = INT_MIN;
        
        for (int left = 0; left < n; left++) {
            vector<int> rowSum(m, 0);
            for (int right = left; right < n; right++) {
                for (int i = 0; i < m; i++) {
                    rowSum[i] += matrix[i][right];
                }
                
                set<int> prefixSums;
                prefixSums.insert(0);
                int currSum = 0;
                
                for (int i = 0; i < m; i++) {
                    currSum += rowSum[i];
                    auto it = prefixSums.lower_bound(currSum - k);
                    if (it != prefixSums.end()) {
                        result = max(result, currSum - *it);
                    }
                    prefixSums.insert(currSum);
                }
            }
        }
        
        return result;
    }
};
