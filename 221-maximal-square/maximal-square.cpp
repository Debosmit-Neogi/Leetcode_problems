class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) return 0;
        int cols = matrix[0].size();

        // dp[r][c] = side length of the largest square
        // whose bottom-right corner is at (r, c)
        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        int max_size = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {

                // Only cells with '1' can form squares
                if (matrix[r][c] == '1') {

                    // Base case: first row or first column
                    // cannot grow beyond size 1
                    if (r == 0 || c == 0) {
                        dp[r][c] = 1;
                    } else {
                        // CORE LOGIC:
                        // A square grows diagonally only if
                        // top, left, and top-left squares exist
                        dp[r][c] = min({
                            dp[r - 1][c],     // top
                            dp[r][c - 1],     // left
                            dp[r - 1][c - 1]  // diagonal
                        }) + 1;
                    }

                    max_size = max(max_size, dp[r][c]);
                }
            }
        }

        // Return area, not side length
        return max_size * max_size;
    }
};
