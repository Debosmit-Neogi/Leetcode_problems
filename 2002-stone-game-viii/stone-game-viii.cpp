class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {

        int n = stones.size();

        // Build prefix sums
        vector<int> prefix(n);

        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        // Base case:
        // Alice can remove all stones.
        int dp = prefix[n - 1];

        // Try taking a smaller prefix.
        // i must be at least 1 because x > 1.
        for (int i = n - 2; i >= 1; i--) {

            dp = max(
                dp,
                prefix[i] - dp
            );
        }

        return dp;
    }
};