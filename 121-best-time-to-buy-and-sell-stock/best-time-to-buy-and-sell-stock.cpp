class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_prof = 0; // Maximum profit
        int min_price = INT_MAX; // Initialize to a very large value
        
        for (int i = 0; i < prices.size(); i++) {
            // Update the minimum price seen so far
            if (prices[i] < min_price) {
                min_price = prices[i];
            }
            // Calculate profit if selling at current price
            int profit = prices[i] - min_price;
            // Update the maximum profit
            max_prof = max(max_prof, profit);
        }
        
        return max_prof;
    }
};
