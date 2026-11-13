
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n) LOG++;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Next strictly greater element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) nxt[i] = st.top();

            st.push(i);
        }

        // Binary lifting tables
        vector<vector<int>> up(LOG, vector<int>(n, n));
        vector<vector<long long>> sum(
            LOG, vector<long long>(n, 0)
        );

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            int j = nxt[i];

            sum[0][i] =
                1LL * nums[i] * (j - i - 1)
                - (pref[j] - pref[i + 1]);
        }

        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                int mid = up[p - 1][i];

                if (mid < n) {
                    up[p][i] = up[p - 1][mid];

                    sum[p][i] =
                        sum[p - 1][i] + sum[p - 1][mid];
                }
            }
        }

        // Minimum operations for nums[l...r]
        auto getCost = [&](int l, int r) -> long long {
            long long cost = 0;
            int cur = l;

            for (int p = LOG - 1; p >= 0; p--) {
                int next = up[p][cur];

                if (next <= r) {
                    cost += sum[p][cur];
                    cur = next;
                }
            }

            // Remaining partial block
            cost += 1LL * nums[cur] * (r - cur)
                    - (pref[r + 1] - pref[cur + 1]);

            return cost;
        };

        long long ans = 0;

        // Binary search maximum valid right endpoint
        for (int l = 0; l < n; l++) {
            int low = l;
            int high = n - 1;
            int best = l - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (getCost(l, mid) <= k) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            ans += best - l + 1;
        }

        return ans;
    }
};
