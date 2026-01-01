#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        
        // Edge case: if either number is "0", result is "0"
        if (num1 == "0" || num2 == "0") return "0";
        
        // Result can have at most m + n digits
        vector<int> result(m + n, 0);
        
        // Multiply each digit from right to left
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;      // tens position
                int p2 = i + j + 1;  // ones position
                
                int sum = mul + result[p2];
                result[p2] = sum % 10;
                result[p1] += sum / 10;
            }
        }
        
        // Build result string, skipping leading zeros
        string str;
        for (int digit : result) {
            if (!(str.empty() && digit == 0)) {
                str += to_string(digit);
            }
        }
        
        return str.empty() ? "0" : str;
    }
};
