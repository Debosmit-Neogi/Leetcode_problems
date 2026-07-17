// basic raw recursive intuition:
// array: [10,9,2,5,3,7,101,18]

// suppose we have a subsequence that ends with 18. so what other digits are possible in the Increasing Subsequence: 10,9,2,5,3,7 but not 101
// suppose we chose 7 -> what other digits are possible before 7 -> 3,5,2 not 9 and 10
// suppose we chose 3 -> what other digits are possible n the IS before 3 -> only 2
// so LIS: 2,3,7,18 [length = 4]


// this was just a solution considering LIS ends with 18. Not necessary that is the LIS. We then have to look at IS ending with 101 and backtrack and so on...

class Solution {
public:
    // given an index return the length of Longest Inc Subsequence if we include the element at that idx 

    
    // int LIS(int idx, vector<int>& nums){
    //     int ans = 1; // if no other element is found, LIS=[arr[idx]] -> len=1

    //     for(int i=0; i<idx; i++){
    //         if(nums[i] < nums[idx]){
    //             // then we can possibly include nums[i] in the Inc subseq
    //             // then we recursively check next possible entry in nums for LIS if we include nums[i] along with nums[idx]

    //             ans = max(ans, LIS(i, nums)+1);
    //         }
            
    //     }
    //     return ans;
    // }
    


    //The above solution with basic recursion works but it gives TLE
    // optimized with DP

    int LIS(int idx, vector<int>& nums, vector<int>& dp){

        // if we have already computed len of LIS at any idx it must be in the dp table
        if(dp[idx] !=-0){
            return dp[idx];
        }

        // else compute and store in dp table
        int ans = 1; // if no other element is found, LIS=[arr[idx]] -> len=1

        for(int i=0; i<idx; i++){
            if(nums[i] < nums[idx]){
                // then we can possibly include nums[i] in the Inc subseq
                // then we recursively check next possible entry in nums for LIS if we include nums[i] along with nums[idx]
                
                ans = max(ans, LIS(i, nums, dp)+1);
                dp[idx] = ans;
                
            }
            
        }
        return ans;
    }
    int lengthOfLIS(vector<int>& nums) {
        int global_max = INT_MIN;
        int curr_max =1;
        vector<int> dp(nums.size(), 0); // create a dp vector containing length of LIS of each idx of nums array

        for(int i=0; i< nums.size(); i++){
            curr_max = LIS(i, nums, dp);
            global_max = max(curr_max, global_max);
        }

        return global_max;

        
    }


};