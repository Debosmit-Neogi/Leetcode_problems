class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long count = 0; // Total number of zero-filled subarrays
        long long consecutiveZeros = 0; // Current run length of consecutive zeros

        
        for (int num : nums) {
            if (num == 0) {
                consecutiveZeros++; // Extend the run
                count += consecutiveZeros;  // Add all subarrays ending at current position
            } else {
                consecutiveZeros = 0; // reset the run (as non zero is encountered)
            }
        }
        
        return count;
    }
};