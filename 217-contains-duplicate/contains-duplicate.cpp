class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        
        unordered_set<int> my_set;

        for(int i=0; i<nums.size(); i++){

            my_set.insert(nums[i]);
        }

        if (my_set.size() < nums.size()){
            return true;
        }

        else{
            return false;
        }

    }

    
};