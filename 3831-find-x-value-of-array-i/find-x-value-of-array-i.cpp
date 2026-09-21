#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);

        // dp[r] = number of subarrays ending at the
        // previous index whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            num %= k;

            vector<long long> new_dp(k, 0);

            // Start a new subarray [num]
            new_dp[num]++;

            // Extend all previous subarrays by num
            for (int r = 0; r < k; r++) {
                if (dp[r] == 0)
                    continue;

                int newRemainder = (r * num) % k;

                new_dp[newRemainder] += dp[r];
            }

            // All subarrays ending at this position
            // contribute to the final answer
            for (int r = 0; r < k; r++) {
                result[r] += new_dp[r];
            }

            dp = new_dp;
        }

        return result;
    }
};