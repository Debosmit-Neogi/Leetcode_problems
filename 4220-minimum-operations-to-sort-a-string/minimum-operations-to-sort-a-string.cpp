class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        if (is_sorted(s.begin(), s.end())) return 0;
        if (n == 2) return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // sort the rest / sort the prefix
        if (s[0] == mn || s[n - 1] == mx) return 1;

        // min exists in [0..n-2]  -> prefix sort then suffix sort
        bool minInPrefix = false;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == mn) { minInPrefix = true; break; }
        }

        // max exists in [1..n-1]  -> suffix sort then prefix sort
        bool maxInSuffix = false;
        for (int i = 1; i < n; i++) {
            if (s[i] == mx) { maxInSuffix = true; break; }
        }

        if (minInPrefix || maxInSuffix) return 2;
        return 3;
    }
};