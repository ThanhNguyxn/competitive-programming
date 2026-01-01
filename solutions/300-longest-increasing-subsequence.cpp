#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<int> tails;
        
        for (int num : nums) {
            // Find the first element in tails that is >= num
            auto it = lower_bound(tails.begin(), tails.end(), num);
            
            if (it == tails.end()) {
                // If no such element, num extends the longest increasing subsequence
                tails.push_back(num);
            } else {
                // Otherwise, replace the found element with num to potentially
                // allow for a longer subsequence later (greedy approach)
                *it = num;
            }
        }
        
        return tails.size();
    }
};
