class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int>lookup;
        for(int i=0;i<n;i++){
                lookup[nums[i]]++;
            }
        int res;
        for(const auto& pair: lookup){
            if(pair.second > floor(n/2)){
                return pair.first;
            }
        }
       return -1;

        }
         
        
    
};