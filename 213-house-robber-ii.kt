class Solution {
    fun rob(nums: IntArray): Int {
        if (nums.isEmpty()) return 0
        if (nums.size == 1) return nums[0]
        
        // Helper function to solve linear House Robber problem
        fun robLinear(start: Int, end: Int): Int {
            var prev1 = 0
            var prev2 = 0
            
            for (i in start..end) {
                val current = maxOf(prev1, prev2 + nums[i])
                prev2 = prev1
                prev1 = current
            }
            return prev1
        }
        
        // Case 1: Rob from index 0 to n-2 (exclude last house)
        // Case 2: Rob from index 1 to n-1 (exclude first house)
        return maxOf(robLinear(0, nums.size - 2), robLinear(1, nums.size - 1))
    }
}
