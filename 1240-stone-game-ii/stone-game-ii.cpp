class Solution {
public:
    int n;
    vector<int> suffix;
    int dp[101][101];

    int solve(int i, int M, vector<int>& piles) {
        // No piles remaining
        if (i == n)
            return 0;

        // Can take all remaining piles
        if (2 * M >= n - i)
            return suffix[i];

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M; X++) {
            if (i + X > n)
                break;

            int nextM = max(M, X);

            // Opponent's maximum stones
            int opponent = solve(i + X, nextM, piles);

            // Total remaining stones - opponent's stones
            int current = suffix[i] - opponent;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = sum of piles[i ... n-1]
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        memset(dp, -1, sizeof(dp));

        return solve(0, 1, piles);
    }
};