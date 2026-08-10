class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[0] = false
        // If there are 0 stones, current player cannot move,
        // so current player loses.

        for (int i = 1; i <= n; i++) {

            for (int x = 1; x * x <= i; x++) {

                int remaining = i - x * x;

                // If opponent is in a losing state,
                // current player can win.
                if (dp[remaining] == false) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};