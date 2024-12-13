class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set <int> look;

        for(int i=0;i<nums.size();i++){
            if(look.find(nums[i])!=look.end()){
                return true;
                
            }

            else{
                look.insert(nums[i]);
            }
        }
        return false;
    }
};