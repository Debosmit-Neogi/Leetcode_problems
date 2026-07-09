class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        int n = nums.size()-1;

        vector<int>prefix(n+1);
        vector<int>postfix(n+1);
        
        
        // fill first element of prefix with nums[0]
        prefix[0] = nums[0];

        // fill last element of postfix with last element of nums
        postfix[n] = nums[n];

        for(int i=1; i<nums.size(); i++){
            prefix[i] = prefix[i-1]*nums[i];
        }

        for(int i = n-1; i>0; i--){
            postfix[i] = postfix[i+1]*nums[i];
        }

        vector<int>ans(n+1);

        for(int i=1; i<=n-1; i++){
              ans[i] = prefix[i-1]*postfix[i+1];
        }

        ans[0] = postfix[1];
        ans[n] = prefix[n-1];

        return ans;
        
    }
};