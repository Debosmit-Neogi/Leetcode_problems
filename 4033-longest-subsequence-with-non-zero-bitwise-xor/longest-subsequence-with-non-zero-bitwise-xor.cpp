class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            totalXor ^= x;

            if (x != 0) {
                hasNonZero = true;
            }
        }

        // Entire array has non-zero XOR
        if (totalXor != 0) {
            return n;
        }

        // Total XOR is zero, but we can remove one non-zero element
        if (hasNonZero) {
            return n - 1;
        }

        // Every element is zero
        return 0;
    }
};