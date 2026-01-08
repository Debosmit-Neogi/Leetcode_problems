class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total =0;
        int max_sum = nums[0];
        int min_sum = nums[0];

        int curr_max = 0;
        int curr_min = 0;

        for(int i=0; i<nums.size(); i++){
            total += nums[i];

            curr_max = max(nums[i], curr_max + nums[i]);
            max_sum = max(curr_max, max_sum);


            curr_min = min(nums[i], curr_min + nums[i]);
            min_sum = min(curr_min, min_sum);

        }

        if (max_sum >= 0){
            return max(max_sum, total-min_sum);
        }

        return max_sum;
    }
};