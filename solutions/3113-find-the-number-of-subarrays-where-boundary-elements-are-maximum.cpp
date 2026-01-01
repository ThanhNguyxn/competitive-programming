class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long count = 0;
        stack<pair<int, long long>> st;
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.top().first < nums[i]) {
                st.pop();
            }
            
            if (!st.empty() && st.top().first == nums[i]) {
                long long cnt = st.top().second;
                count += cnt + 1;
                st.pop();
                st.push({nums[i], cnt + 1});
            } else {
                count++;
                st.push({nums[i], 1});
            }
        }
        
        return count;
    }
};
