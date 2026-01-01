#include <stdio.h>

// Helper function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Helper function to find minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

int maxProduct(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int maxSoFar = nums[0];
    int minSoFar = nums[0];
    int result = maxSoFar;

    for (int i = 1; i < numsSize; i++) {
        int curr = nums[i];
        
        // If current number is negative, swapping max and min gives us a chance 
        // to turn a very small negative number into a very large positive number
        if (curr < 0) {
            int temp = maxSoFar;
            maxSoFar = minSoFar;
            minSoFar = temp;
        }

        maxSoFar = max(curr, maxSoFar * curr);
        minSoFar = min(curr, minSoFar * curr);

        result = max(result, maxSoFar);
    }

    return result;
}
