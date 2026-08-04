class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        vector<int>ans;

        for(int i=0; i<nums.size()-1; ){
            if(nums[i+1]-nums[i] !=1){
                int diff = nums[i+1]-nums[i];
                while(diff>1){
                    ans.push_back(nums[i] + diff-1);
                    diff--;
                }
                i++;
            }

            else{
                // continue;
                i++;
            }
        }

        sort(ans.begin(), ans.end());
        return ans;
        
    }
};