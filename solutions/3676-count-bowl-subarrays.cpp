class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long count = 0;
        
        vector<int> leftGreater(n, -1), rightGreater(n, n);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                rightGreater[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) {
                leftGreater[i] = st.top();
            }
            st.push(i);
        }
        
        for (int m = 0; m < n; m++) {
            int l = leftGreater[m];
            int r = rightGreater[m];
            
            if (l >= 0 && r < n) {
                count++;
            }
        }
        
        return count;
    }
};
