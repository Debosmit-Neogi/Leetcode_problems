
class Solution {
public:

    int rob_index(vector<int>& nums, int left, int right){

        int n = right - left + 1; // essentially calculating the number of houses we are considering

        if(n==0) return 0;
        if(n==1) return nums[left];

        vector<int>dp(n, INT_MAX);
        dp[0] = nums[left];
        dp[1] = max(nums[left], nums[left + 1]);


        for(int i=2; i<n; i++){

            dp[i] = max((nums[left+i] + dp[i-2]), (dp[i-1])); // 2 cases: rob last house or not 
        }
        return dp[n-1];
    }
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n==0) return 0;
        if (n==1) return nums[0];
        return max(rob_index(nums,1, n-1), rob_index(nums, 0, n-2)); // max loot if we consider: last house or the first house (in circular array can't take both)
    }
};