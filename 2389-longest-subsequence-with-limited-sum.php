class Solution {

    /**
     * @param Integer[] $nums
     * @param Integer[] $queries
     * @return Integer[]
     */
    function answerQueries($nums, $queries) {
        // Sort nums to pick smallest elements first for longest subsequence
        sort($nums);
        
        // Calculate prefix sums
        $n = count($nums);
        $prefix = array_fill(0, $n, 0);
        $prefix[0] = $nums[0];
        for ($i = 1; $i < $n; $i++) {
            $prefix[$i] = $prefix[$i - 1] + $nums[$i];
        }
        
        $answer = [];
        foreach ($queries as $q) {
            // Binary search to find the count of elements
            // We want to find the largest index i such that prefix[i] <= q
            // The number of elements will be i + 1
            $count = $this->upperBound($prefix, $q);
            $answer[] = $count;
        }
        
        return $answer;
    }
    
    /**
     * Helper function to find the index of the first element greater than target
     * Returns the count of elements <= target
     */
    function upperBound($arr, $target) {
        $left = 0;
        $right = count($arr) - 1;
        $ans = -1;
        
        while ($left <= $right) {
            $mid = intval($left + ($right - $left) / 2);
            
            if ($arr[$mid] <= $target) {
                $ans = $mid;
                $left = $mid + 1;
            } else {
                $right = $mid - 1;
            }
        }
        
        return $ans + 1;
    }
}
