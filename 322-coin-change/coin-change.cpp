class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {

        if(amount<=0) return 0;

        vector<int>dp(amount+1, INT_MAX);
        dp[0] = 0;
        for(int i=1; i<dp.size(); i++){
            for(int coin=0; coin<coins.size(); coin++){
                if(coins[coin] <=i && dp[i-coins[coin]]!=INT_MAX){
                    dp[i] = min(dp[i], 1+dp[i-coins[coin] ]);
                }
                
            }
        }

        if(dp[amount] == INT_MAX) return -1;

        return dp[amount];
        
    }
};