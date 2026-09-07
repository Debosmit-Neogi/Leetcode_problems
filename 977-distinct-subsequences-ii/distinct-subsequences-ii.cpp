class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        // dp = number of distinct subsequences including empty subsequence
        long long dp = 1;

        // last[c] = value of dp before the previous occurrence of c
        vector<long long> last(26, 0);

        for (char c : s) {
            int idx = c - 'a';

            long long new_dp = (2 * dp % MOD - last[idx] + MOD) % MOD;

            last[idx] = dp;
            dp = new_dp;
        }

        // Remove the empty subsequence
        return (dp - 1 + MOD) % MOD;
    }
};