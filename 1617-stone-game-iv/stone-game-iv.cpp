class Solution {
public:
    bool winnerSquareGame(int n) {

        // dp[i] = true if the current player
        // can force a win with i stones.
        vector<bool> dp(n + 1, false);

        // dp[0] = false
        // No stones means the current player
        // cannot make a move.

        for (int i = 1; i <= n; i++) {

            // Try every perfect square <= i
            for (int x = 1; x * x <= i; x++) {

                int square = x * x;

                // State after making this move
                int remaining = i - square;

                // If the opponent is in a losing state,
                // then this is a winning move.
                if (dp[remaining] == false) {

                    dp[i] = true;

                    // One winning move is enough.
                    break;
                }
            }
        }

        return dp[n];
    }
};