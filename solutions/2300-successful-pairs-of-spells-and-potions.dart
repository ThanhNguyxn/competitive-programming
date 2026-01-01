class Solution {
  List<int> successfulPairs(List<int> spells, List<int> potions, int success) {
    // Sort potions to enable binary search
    potions.sort();
    int m = potions.length;
    List<int> result = [];

    for (int spell in spells) {
      // We need to find the smallest index i such that potions[i] * spell >= success
      // This is equivalent to finding the first potion >= ceil(success / spell)
      
      int left = 0;
      int right = m;
      
      while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (potions[mid] * spell >= success) {
          right = mid;
        } else {
          left = mid + 1;
        }
      }
      
      // All potions from index 'left' to the end are successful
      result.add(m - left);
    }

    return result;
  }
}
