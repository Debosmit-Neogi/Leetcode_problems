class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0; // Handle empty input

        sort(nums.begin(), nums.end()); // Sort the array
        int maxCount = 1; // To track the longest sequence
        int count = 1; // To count the current sequence

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                continue; // Skip duplicates
            }
            if (nums[i] == nums[i - 1] + 1) {
                count++; // Extend the current sequence
            } else {
                maxCount = max(maxCount, count); // Update the maximum sequence length
                count = 1; // Reset count for a new sequence
            }
        }
        maxCount = max(maxCount, count); // Final check for the last sequence
        return maxCount;
    }
};
