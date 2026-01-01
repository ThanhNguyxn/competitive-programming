class Solution {
    func lengthOfLongestSubstring(_ s: String) -> Int {
        var charIndexMap = [Character: Int]()
        var maxLength = 0
        var left = 0
        let chars = Array(s)
        
        for (right, char) in chars.enumerated() {
            if let index = charIndexMap[char], index >= left {
                left = index + 1
            }
            
            charIndexMap[char] = right
            maxLength = max(maxLength, right - left + 1)
        }
        
        return maxLength
    }
}
