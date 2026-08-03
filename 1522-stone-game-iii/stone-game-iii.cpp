class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // dp[i] = Maximum score difference (current player - opponent)
        // starting from index i.
        vector<int> dp(n + 1, 0);

        // dp[n] = 0 because no stones are left.
        dp[n] = 0;

        // Fill the DP table from the end towards the beginning.
        for (int i = n - 1; i >= 0; i--) {

            // Initialize with a very small value.
            dp[i] = INT_MIN;

            int currSum = 0;

            // Try taking 1, 2, or 3 stones.
            for (int k = 0; k < 3 && i + k < n; k++) {

                // Add the value of the current stone.
                currSum += stoneValue[i + k];

                // Score difference if we take (k + 1) stones.
                // After our move, the opponent starts at i + k + 1,
                // whose advantage is dp[i + k + 1].
                dp[i] = max(dp[i], currSum - dp[i + k + 1]);
            }
        }

        // Decide the winner based on the final score difference.
        if (dp[0] > 0)
            return "Alice";
        else if (dp[0] < 0)
            return "Bob";
        else
            return "Tie";
    }
};