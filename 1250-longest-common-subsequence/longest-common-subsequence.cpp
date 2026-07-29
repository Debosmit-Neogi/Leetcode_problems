class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {

        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){

                // If the current characters match,
                // include this character in the LCS.

                if(text1[i-1] == text2[j-1]){
                    // Move diagonally because both characters
                    // are used in the subsequence.
                    dp[i][j] = dp[i-1][j-1] + 1; // since text match take characters from both text1 and text2 in the LCS
                }

                // if they don't match
                 // Characters don't match.
                    // We have two choices:
                    //
                    // 1. Ignore current character of text1
                    //    -> dp[i-1][j]
                    //
                    // 2. Ignore current character of text2
                    //    -> dp[i][j-1]
                    //
                    // Take the better option.

                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[n][m];
        



        

    }
};