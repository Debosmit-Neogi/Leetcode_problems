
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        multiset<long long> st;
        long long ans = LLONG_MAX;

        for (int i = l; i <= n; i++) {

            // Add the smallest valid starting index
            st.insert(prefix[i - l]);

            // Remove indices that are too far away
            if (i - r - 1 >= 0) {
                auto it = st.find(prefix[i - r - 1]);
                if (it != st.end()) {
                    st.erase(it);
                }
            }

            // Find largest prefix sum strictly smaller than prefix[i]
            auto it = st.lower_bound(prefix[i]);

            if (it != st.begin()) {
                --it;

                long long sum = prefix[i] - *it;

                if (sum > 0) {
                    ans = min(ans, sum);
                }
            }
        }

        return ans == LLONG_MAX ? -1 : (int)ans;
    }
};
