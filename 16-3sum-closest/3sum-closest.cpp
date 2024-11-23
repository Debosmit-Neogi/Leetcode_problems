class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        // Sort the vector
        sort(nums.begin(), nums.end());
        int min_diff = INT_MAX;
        int sum;
        int closest_sum=0;
        for(int i=0; i<nums.size(); i++){

            // start left/right pointer approach

            int left = i+1;
            int right = nums.size()-1;

            while(left<right){
                sum = nums[i]+nums[left]+nums[right];
                if(abs(target-sum)< min_diff){
                    min_diff = abs(sum-target);
                    closest_sum = sum;

                }
                if(sum>target){
                    right--;
                }

                else if(sum<target){
                    left++;
                }

                else{
                    return sum;
                }
            }
            
        }
    return closest_sum;
    }
};