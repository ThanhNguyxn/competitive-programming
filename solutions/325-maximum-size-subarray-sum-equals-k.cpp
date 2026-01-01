class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<long long, int> prefixMap;
        prefixMap[0] = -1;
        long long sum = 0;
        int maxLen = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (prefixMap.count(sum - k)) {
                maxLen = max(maxLen, i - prefixMap[sum - k]);
            }
            if (!prefixMap.count(sum)) {
                prefixMap[sum] = i;
            }
        }
        
        return maxLen;
    }
};
