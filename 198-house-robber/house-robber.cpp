class Solution {
public:
    int rob(vector<int>& nums) {

        int n = nums.size();

        if (n==0) return 0;
        if (n==1) return nums[0];
        vector<int>dp(nums.size(), INT_MAX); // dp[i] stores max loot possible if ith house is included
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);

        for(int i=2; i<nums.size(); i++){
            dp[i] =  max((nums[i] + dp[i-2]), (dp[i-1])); // 2 cases possible: we rob ith house or we don't. we take the maximum loot
        }
        return dp[n-1];
    }
};