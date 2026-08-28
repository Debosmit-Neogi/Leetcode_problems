class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Count characters in s
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // A palindrome can have at most one odd-frequency character
        int odd = 0;
        int middle = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                middle = i;
            }
        }

        if (odd > 1) {
            return "";
        }

        // Number of characters in the first half
        int m = n / 2;

        // Counts available for the first half
        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) {
            halfCnt[i] = cnt[i] / 2;
        }

        // Construct the full palindrome from its first half
        auto buildPalindrome = [&](const string& half) {
            string res = half;

            // Add middle character for odd length
            if (n % 2) {
                res += char('a' + middle);
            }

            // Add reverse of first half
            for (int i = m - 1; i >= 0; i--) {
                res += half[i];
            }

            return res;
        };

        string answer = "";

        /*
         * We construct the first half.
         *
         * For every possible pivot:
         *
         *   [same as target] [larger character] [smallest rest]
         *
         * This gives the smallest palindrome whose first
         * difference from target occurs at that position.
         */
        for (int pivot = 0; pivot <= m; pivot++) {

            vector<int> available = halfCnt;
            string prefix;
            bool possible = true;

            // Match target before the pivot
            for (int i = 0; i < pivot; i++) {
                int c = target[i] - 'a';

                if (available[c] == 0) {
                    possible = false;
                    break;
                }

                available[c]--;
                prefix += target[i];
            }

            if (!possible) {
                continue;
            }

            // -------------------------------------------------
            // Case 1:
            // Choose a character greater than target[pivot]
            // -------------------------------------------------
            if (pivot < m) {

                int targetChar = target[pivot] - 'a';

                for (int c = targetChar + 1; c < 26; c++) {

                    if (available[c] == 0) {
                        continue;
                    }

                    vector<int> remaining = available;
                    remaining[c]--;

                    string half = prefix;
                    half += char('a' + c);

                    // Put remaining characters in sorted order
                    for (int x = 0; x < 26; x++) {
                        half += string(
                            remaining[x],
                            char('a' + x)
                        );
                    }

                    string candidate = buildPalindrome(half);

                    if (candidate > target &&
                        (answer.empty() || candidate < answer)) {
                        answer = candidate;
                    }

                    /*
                     * For this pivot, the smallest character
                     * greater than target[pivot] is optimal.
                     */
                    break;
                }
            }

            // -------------------------------------------------
            // Case 2:
            // The entire first half equals target's first half
            //
            // The palindrome can still be > target because
            // of the second half.
            // -------------------------------------------------
            else {

                string half = prefix;

                for (int x = 0; x < 26; x++) {
                    half += string(
                        available[x],
                        char('a' + x)
                    );
                }

                string candidate = buildPalindrome(half);

                if (candidate > target &&
                    (answer.empty() || candidate < answer)) {
                    answer = candidate;
                }
            }
        }

        return answer;
    }
};