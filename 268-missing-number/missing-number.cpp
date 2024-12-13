class Solution {
public:
    int missingNumber(vector<int>& nums) {

        int n = nums.size();

        int sum = ((n)*(n+1))/2 ;
        int new_sum = 0;

        for(int i=0; i<n; i++){
            new_sum += nums[i];
        }
        int diff = sum - new_sum;
    return diff;
    }
    
};