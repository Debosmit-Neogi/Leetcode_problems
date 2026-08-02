class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();

        // dp[i][j] = Maximum score difference (current player - opponent)
        // that the current player can achieve from piles[i...j].
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base Case:
        // If there is only one pile, the current player takes it,
        // so the score difference is equal to the number of stones.
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }

        // Consider all subarrays of length 2 to n
        for (int len = 2; len <= n; len++) {

            // Starting index of the subarray
            for (int i = 0; i + len - 1 < n; i++) {

                // Ending index
                int j = i + len - 1;

                // Option 1: Take the left pile.
                // After taking piles[i], the opponent becomes the current player
                // on the remaining subarray (i+1...j).
                // Since dp[i+1][j] represents the opponent's advantage,
                // subtract it from the stones we gain.
                int takeLeft = piles[i] - dp[i + 1][j];

                // Option 2: Take the right pile.
                // Similar logic applies for the remaining subarray (i...j-1).
                int takeRight = piles[j] - dp[i][j - 1];

                // Choose the option that gives the maximum score difference.
                dp[i][j] = max(takeLeft, takeRight);
            }
        }

        // If the maximum score difference is positive,
        // Alice (the first player) collects more stones than Bob.
        return dp[0][n - 1] > 0;
    }
};