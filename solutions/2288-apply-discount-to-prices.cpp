#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Solution {
public:
    string discountPrices(string sentence, int discount) {
        stringstream ss(sentence);
        string word;
        string result;
        
        while (ss >> word) {
            if (!result.empty()) result += " ";
            
            // Check if word is a valid price: starts with '$' and followed by digits only
            if (word.size() > 1 && word[0] == '$') {
                bool isValidPrice = true;
                for (int i = 1; i < word.size(); ++i) {
                    if (!isdigit(word[i])) {
                        isValidPrice = false;
                        break;
                    }
                }
                
                if (isValidPrice) {
                    // Parse the price and apply discount
                    long long price = stoll(word.substr(1));
                    double discountedPrice = price * (100.0 - discount) / 100.0;
                    
                    // Format with exactly 2 decimal places
                    ostringstream oss;
                    oss << fixed << setprecision(2) << discountedPrice;
                    result += "$" + oss.str();
                } else {
                    result += word;
                }
            } else {
                result += word;
            }
        }
        
        return result;
    }
};
