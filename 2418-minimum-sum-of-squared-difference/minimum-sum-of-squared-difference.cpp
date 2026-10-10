class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<int> diff(n);
        long long sum = 0;
        int mx = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            sum += diff[i];
            mx = max(mx, diff[i]);
        }

        if (sum <= k) return 0;

        vector<long long> freq(mx + 1, 0);

        for (int d : diff) {
            freq[d]++;
        }

        for (int d = mx; d > 0 && k > 0; d--) {
            long long count = freq[d];
            long long operations = min(k, count);

            // Reduce as many differences as possible by one.
            freq[d] -= operations;
            freq[d - 1] += operations;
            k -= operations;
        }

        long long ans = 0;

        for (int d = 1; d <= mx; d++) {
            ans += freq[d] * d * d;
        }

        return ans;
    }
};