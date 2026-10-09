
class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open_needed = 0;

        for (char ch : s) {
            if (ch == '(') {
                // If the remaining ')' requirement is odd,
                // insert one ')' to complete the previous pair.
                if (open_needed % 2 == 1) {
                    insertions++;
                    open_needed--;
                }

                // Each '(' requires two ')'
                open_needed += 2;
            } 
            else {
                open_needed--;

                // No opening parenthesis available
                if (open_needed < 0) {
                    insertions++;  // Insert '(' before ')'
                    open_needed = 1;
                }
            }
        }

        // Insert missing closing parentheses
        return insertions + open_needed;
    }
};
