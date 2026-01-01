#include <vector>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        // If the array is not rotated (e.g., [1, 2, 3])
        if (nums[left] <= nums[right]) return nums[left];
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than right element, 
            // the minimum must be in the right half (excluding mid)
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // Otherwise, the minimum is in the left half (including mid)
            else {
                right = mid;
            }
        }
        
        return nums[left];
    }
};
