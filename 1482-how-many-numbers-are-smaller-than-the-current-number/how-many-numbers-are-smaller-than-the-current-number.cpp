class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int>res(nums.size());
        for(int i=0; i<nums.size(); i++){
            int count = 0;
            for(int j = 0; j<nums.size(); j++){
                if(nums[j]<nums[i]){
                    count++;
                }
            }
            res[i] = count;
        }
        return res;
    }
};