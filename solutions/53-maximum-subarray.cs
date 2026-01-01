public class Solution {
    public int MaxSubArray(int[] nums) {
        // Kadane's Algorithm
        // Initialize currentMax and globalMax with the first element
        int currentMax = nums[0];
        int globalMax = nums[0];
        
        for (int i = 1; i < nums.Length; i++) {
            // Either extend the existing subarray or start a new one at current element
            currentMax = Math.Max(nums[i], currentMax + nums[i]);
            
            // Update global maximum if current subarray sum is larger
            globalMax = Math.Max(globalMax, currentMax);
        }
        
        return globalMax;
    }
}
