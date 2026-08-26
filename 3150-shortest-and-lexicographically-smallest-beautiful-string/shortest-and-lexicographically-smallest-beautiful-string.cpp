class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        int left = 0;
        int ones = 0;

        int bestLen = INT_MAX;
        string answer = "";

        for (int right = 0; right < n; right++) {

            // Add current character to the window
            if (s[right] == '1') {
                ones++;
            }

            // We only care about windows containing exactly k ones
            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            // If the window has exactly k ones
            if (ones == k) {

                // Remove leading zeroes.
                // They are unnecessary and make the substring longer.
                while (s[left] == '0') {
                    left++;
                }

                int len = right - left + 1;
                string current = s.substr(left, len);

                // Update if:
                // 1. Current substring is shorter, or
                // 2. Same length but lexicographically smaller
                if (len < bestLen ||
                    (len == bestLen && current < answer)) {

                    bestLen = len;
                    answer = current;
                }
            }
        }

        return answer;
    }
};