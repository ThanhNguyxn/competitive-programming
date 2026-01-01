use std::collections::HashMap;

impl Solution {
    pub fn subarrays_with_k_distinct(nums: Vec<i32>, k: i32) -> i32 {
        // The number of subarrays with exactly K distinct integers is:
        // (Subarrays with at most K distinct) - (Subarrays with at most K-1 distinct)
        Self::at_most_k(&nums, k) - Self::at_most_k(&nums, k - 1)
    }

    fn at_most_k(nums: &Vec<i32>, k: i32) -> i32 {
        let mut left = 0;
        let mut count = 0;
        let mut freq = HashMap::new();

        for (right, &num) in nums.iter().enumerate() {
            *freq.entry(num).or_insert(0) += 1;

            while freq.len() > k as usize {
                if let Some(val) = freq.get_mut(&nums[left]) {
                    *val -= 1;
                    if *val == 0 {
                        freq.remove(&nums[left]);
                    }
                }
                left += 1;
            }

            count += (right - left + 1) as i32;
        }
        count
    }
}
