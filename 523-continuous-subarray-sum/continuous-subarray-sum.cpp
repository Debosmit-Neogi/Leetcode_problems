class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        
        // define map to store: remainder, idx where it appeared
        unordered_map<int,int> remainderIdx;

        // Prefix sum before the array starts is 0 at index -1.
        // This helps detect subarrays starting from index 0.

        remainderIdx[0] = -1;

        int prefixSum = 0;

        if(nums.size() <2){
            return false;
        }

        for(int i=0; i<nums.size(); i++){

            // update running prefix sum

            prefixSum += nums[i];
            
            // compute remainder of the prefix sum
            // if k == 0, we can't take modulo. so remiander = prefix sum itself

            int remainder = 0;

            if(k==0){
                remainder = prefixSum;
            }

            else
                remainder = prefixSum % k;


            // If we've seen this remainder before,
            // then the subarray between the previous index and current index
            // has a sum divisible by k.

            if(remainderIdx.count(remainder)){

                // length of subarray has to be >=2

                

                if(i - remainderIdx[remainder] >=2){
                    return true;
                }

                
            }

            else{
                    remainderIdx[remainder] = i; // Store only the FIRST occurrence of each remainder.
                }

           

        }
         return false;
        
    }
};