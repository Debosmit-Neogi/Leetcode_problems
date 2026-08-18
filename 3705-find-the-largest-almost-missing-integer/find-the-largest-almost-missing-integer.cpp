class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {

        unordered_map<int, int> count;

        int n = nums.size();

        // Process every subarray of size k
        for (int i = 0; i <= n - k; i++) {

            // Store distinct elements of this window
            unordered_set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            // This number appears in this subarray
            // exactly once, regardless of how many
            // times it occurs inside the window.
            for (int x : seen) {
                count[x]++;
            }
        }

        int answer = -1;

        // Find the largest number that appears
        // in exactly one size-k subarray
        for (auto& [x, freq] : count) {
            if (freq == 1) {
                answer = max(answer, x);
            }
        }

        return answer;
    }
};