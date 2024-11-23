class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size(); // Size of the array
        
        // Handle cases where k is greater than the size of the array
        k = k % n;
        if (k == 0) return; // No rotation needed if k is 0 or a multiple of n

        // Step 1: Reverse the entire array
        reverse(nums.begin(), nums.end());
        // Now the array is reversed: [n-1, ..., 1, 0]

        // Step 2: Reverse the first k elements
        reverse(nums.begin(), nums.begin() + k);
        // Now the first k elements are in order, the rest is still reversed

        // Step 3: Reverse the remaining n-k elements
        reverse(nums.begin() + k, nums.end());
        // Now the entire array is rotated to the right by k steps
    }
};
