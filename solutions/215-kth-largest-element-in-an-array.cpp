#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // nth_element partially sorts the range [first, last) such that:
        // - The element at the nth position is the one that would be there if sorted.
        // - All elements before nth are <= elements after nth.
        // By using greater<int>(), we find the k-th largest (which is at index k-1).
        
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
        return nums[k - 1];
    }
};
