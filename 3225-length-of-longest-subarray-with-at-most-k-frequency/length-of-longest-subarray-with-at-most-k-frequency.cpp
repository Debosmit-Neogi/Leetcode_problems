class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {

        // Stores the frequency of each number
        // inside the current sliding window.
        unordered_map<int, int> freq;

        // Left boundary of our sliding window
        int left = 0;

        // Stores the maximum length found so far
        int ans = 0;

        // Expand the window by moving right
        for (int right = 0; right < nums.size(); right++) {

            // Add the current element to the window
            freq[nums[right]]++;

            // If the frequency of nums[right] becomes
            // greater than k, the window is invalid.
            //
            // Keep removing elements from the left
            // until the window becomes valid again.
            while (freq[nums[right]] > k) {

                // Remove nums[left] from the window
                freq[nums[left]]--;

                // Move the left boundary forward
                left++;
            }

            // At this point, the window [left ... right]
            // is guaranteed to be a good subarray.
            //
            // Length of the current window:
            // right - left + 1
            ans = max(ans, right - left + 1);
        }

        // Return the longest good subarray length
        return ans;
    }
};