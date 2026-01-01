package main

func rob(nums []int) int {
    if len(nums) == 0 {
        return 0
    }
    
    // prev1 represents the max money robbed up to the previous house
    // prev2 represents the max money robbed up to the house before the previous one
    prev1 := 0
    prev2 := 0
    
    for _, num := range nums {
        // At each house, we can either:
        // 1. Rob this house (num) + max money from 2 houses ago (prev2)
        // 2. Skip this house and keep max money from previous house (prev1)
        newMax := prev1
        if prev2 + num > prev1 {
            newMax = prev2 + num
        }
        
        prev2 = prev1
        prev1 = newMax
    }
    
    return prev1
}
