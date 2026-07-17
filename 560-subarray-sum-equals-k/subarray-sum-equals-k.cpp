// ALGO:
// for every element: 
// prefix += nums[i]

// need = prefix-k

// if need exists
//     answer += frequency

// frequency[prefix]++

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        unordered_map<int,int>mp;

        mp[0] = 1;

        int prefix = 0;
        int ans = 0;

        for(int x: nums){

            prefix = prefix + x;

            // we need to find prefix - k
            int need = prefix-k;

            // present in the map
            if(mp.find(need) != mp.end()){
                ans+= mp[need];
            }

            mp[prefix]++;
        }

        return ans;
        
    }
};