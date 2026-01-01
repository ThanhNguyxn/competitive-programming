class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int left = i + 1;
            int right = n - i;
            int totalSubarrays = left * right;
            int oddSubarrays = (totalSubarrays + 1) / 2;
            sum += oddSubarrays * arr[i];
        }
        return sum;
    }
};
