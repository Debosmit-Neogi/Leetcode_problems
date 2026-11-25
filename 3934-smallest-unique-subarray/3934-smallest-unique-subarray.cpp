
class Solution {
public:
    static constexpr long long MOD1 = 1000000007;
    static constexpr long long MOD2 = 1000000009;
    static constexpr long long BASE = 911382323;

    bool check(int len, vector<int>& nums) {
        int n = nums.size();

        long long power1 = 1, power2 = 1;

        for (int i = 0; i < len; i++) {
            power1 = power1 * BASE % MOD1;
            power2 = power2 * BASE % MOD2;
        }

        long long h1 = 0, h2 = 0;

        // Hash of the first window
        for (int i = 0; i < len; i++) {
            h1 = (h1 * BASE + nums[i]) % MOD1;
            h2 = (h2 * BASE + nums[i]) % MOD2;
        }

        unordered_map<uint64_t, int> freq;

        auto getKey = [&](long long a, long long b) {
            return (uint64_t(a) << 32) | uint64_t(b);
        };

        freq[getKey(h1, h2)]++;

        // Calculate hashes of remaining windows
        for (int i = len; i < n; i++) {
            h1 = (h1 * BASE - nums[i - len] * power1
                  % MOD1 + nums[i] + MOD1) % MOD1;

            h2 = (h2 * BASE - nums[i - len] * power2
                  % MOD2 + nums[i] + MOD2) % MOD2;

            freq[getKey(h1, h2)]++;
        }

        // Check if any subarray occurs exactly once
        for (auto& [hash, count] : freq) {
            if (count == 1)
                return true;
        }

        return false;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        int low = 1;
        int high = nums.size();
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(mid, nums)) {
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
