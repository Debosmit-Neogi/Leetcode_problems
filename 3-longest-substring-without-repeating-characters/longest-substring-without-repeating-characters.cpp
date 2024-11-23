class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int maxlen = 0; // Initialize maxlen to 0
        unordered_set<char> visited; // Use unordered_set to track visited characters
        int i = 0, j = 0; // Two pointers for the sliding window
        
        while (j < s.size()) {
            if (visited.find(s[j]) == visited.end()) { // If s[j] is not in the set
                visited.insert(s[j]);
                maxlen = max(maxlen, j - i + 1); // Update maxlen
                j++; // Expand the window
            } else {
                visited.erase(s[i]); // Remove s[i] from the set
                i++; // Shrink the window
            }
        }
        return maxlen;
    }
};