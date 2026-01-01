#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> brackets = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        for (char c : s) {
            // If it's a closing bracket
            if (brackets.count(c)) {
                // Check if stack is empty or top doesn't match
                if (st.empty() || st.top() != brackets[c]) {
                    return false;
                }
                st.pop();
            } else {
                // It's an opening bracket, push to stack
                st.push(c);
            }
        }
        
        // Valid only if stack is empty at the end
        return st.empty();
    }
};
