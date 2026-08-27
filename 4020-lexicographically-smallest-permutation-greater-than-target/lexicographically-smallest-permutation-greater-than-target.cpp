class Solution {
public:
    string lexGreaterPermutation(string s, string target) {

        int n = s.size();

        // Count characters in s
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Number of characters matched with target
        int i = 0;

        while (i < n && freq[target[i] - 'a'] > 0) {
            freq[target[i] - 'a']--;
            i++;
        }

        /*
            We now try to make the answer strictly greater.

            If i < n:
                target[i] could not be matched.
                We can try to replace target[i] directly.

            If i == n:
                We matched the entire target.
                We must backtrack from the last position.
        */

        int start = i;

        if (i == n) {
            start = n - 1;
        }

        // Try positions from right to left
        for (int j = start; j >= 0; j--) {

            /*
                If j is a matched position, restore its character
                because we are going to replace it.

                If j == i and i < n, target[i] was never consumed,
                so there is nothing to restore.
            */
            if (j < i) {
                freq[target[j] - 'a']++;
            }

            // Find the smallest available character
            // that is greater than target[j].
            int targetChar = target[j] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {

                if (freq[c] == 0) {
                    continue;
                }

                string ans;

                // Keep everything before j equal to target
                ans = target.substr(0, j);

                // Put the smallest possible larger character
                ans += char('a' + c);

                // Use this character
                freq[c]--;

                // Put all remaining characters in sorted order
                for (int x = 0; x < 26; x++) {
                    ans += string(freq[x], char('a' + x));
                }

                return ans;
            }
        }

        return "";
    }
};