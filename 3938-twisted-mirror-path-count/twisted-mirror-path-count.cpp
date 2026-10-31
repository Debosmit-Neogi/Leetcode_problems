
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0]: Arriving at (i,j) from the left.
        // dp[i][j][1]: Arriving at (i,j) from above.
        vector<vector<vector<long long>>> dp(
            m, vector<vector<long long>>(n, vector<long long>(2, 0))
        );

        // Starting position.
        if (grid[0][0] == 1) return 0;

        dp[0][0][0] = 1;
        dp[0][0][1] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                long long ways = (dp[i][j][0] + dp[i][j][1]) % MOD;

                if (i == 0 && j == 0) {
                    ways = 1;
                }

                if (grid[i][j] == 0) {

                    // Move right.
                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + ways) % MOD;
                    }

                    // Move down.
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + ways) % MOD;
                    }

                } else {

                    // Entered mirror from left: reflect downward.
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                    }

                    // Entered mirror from above: reflect rightward.
                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + dp[i][j][1]) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};
