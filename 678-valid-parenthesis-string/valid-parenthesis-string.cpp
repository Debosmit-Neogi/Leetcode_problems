class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' acts as ')'
                high++;  // '*' acts as '('
            }

            // Even the maximum possible number of '(' is negative
            if (high < 0)
                return false;

            // We cannot have fewer than 0 unmatched '('
            low = max(low, 0);
        }

        // Valid if we can end with exactly 0 unmatched '('
        return low == 0;
    }
};