class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        // The problem guarantees that the FINAL answer
        // fits inside a signed 32-bit integer.
        const long long LIMIT = INT_MAX;

        /*
            dp[j] = number of ways to form t[0 ... j-1]
                    using the characters of s processed so far.

            dp[0] = 1 because there is exactly one way
            to form an empty string: choose nothing.

            Initially:

                dp = [1, 0, 0, 0, ...]

            Meaning:
                1 way to form ""
                0 ways to form "t"
                0 ways to form "t[0..1]"
                etc.
        */
        vector<long long> dp(m + 1, 0);

        dp[0] = 1;

        /*
            Process every character of s.
        */
        for (int i = 1; i <= n; i++) {

            /*
                Iterate backwards.

                This is VERY important for 1D DP.

                If:

                    s[i - 1] == t[j - 1]

                then we have two choices:

                1. Use s[i-1]
                   -> dp[j-1]

                2. Skip s[i-1]
                   -> dp[j]

                Therefore:

                    new_dp[j] = old_dp[j] + old_dp[j-1]

                By iterating backwards, dp[j-1] is still
                the value from the previous iteration.
            */
            for (int j = m; j >= 1; j--) {

                /*
                    We can only use the current character
                    if it matches the current character of t.
                */
                if (s[i - 1] == t[j - 1]) {

                    /*
                        We need:

                            dp[j] + dp[j-1]

                        However, these values can become
                        extremely large.

                        We only care about values up to
                        INT_MAX because the FINAL answer
                        is guaranteed to fit in INT_MAX.

                        So instead of calculating:

                            dp[j] + dp[j-1]

                        directly, first check whether the
                        addition would exceed INT_MAX.

                        This prevents integer overflow.
                    */
                    if (dp[j] > LIMIT - dp[j - 1]) {

                        // The value is larger than INT_MAX.
                        // We don't need its exact value anymore.
                        dp[j] = LIMIT;

                    } else {

                        // Safe addition.
                        dp[j] += dp[j - 1];
                    }
                }

                /*
                    If s[i-1] != t[j-1], we cannot use the
                    current character to construct t[j-1].

                    Therefore dp[j] remains unchanged.
                */
            }
        }

        /*
            dp[m] contains the number of distinct subsequences
            of s that are equal to t.

            The problem guarantees that the FINAL answer
            is <= INT_MAX, so converting to int is safe.
        */
        return (int)dp[m];
    }
};