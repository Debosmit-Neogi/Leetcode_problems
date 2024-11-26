class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, sum = 0, min_length = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            while (sum >= target) {
                min_length = min(min_length, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return min_length == INT_MAX ? 0 : min_length;
    }
};
