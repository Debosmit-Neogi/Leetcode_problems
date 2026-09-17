class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // prefix sum -> latest index
        unordered_map<long long, int> mp;

        // best[i] = shortest target-sum subarray
        // completely within [0..i]
        vector<int> best(n, INF);

        long long prefix = 0;
        mp[0] = -1;

        int ans = INF;

        for (int i = 0; i < n; i++) {
            prefix += arr[i];

            // By default, carry forward the best answer
            // found up to i-1.
            if (i > 0)
                best[i] = best[i - 1];

            // Need prefix[j-1] = prefix - target
            if (mp.count(prefix - target)) {
                int start = mp[prefix - target];
                int len = i - start;

                // We have a previous non-overlapping
                // target-sum subarray.
                if (start >= 0 && best[start] != INF) {
                    ans = min(ans, len + best[start]);
                }

                // This subarray may itself be the shortest
                // one ending at/before i.
                best[i] = min(best[i], len);
            }

            mp[prefix] = i;
        }

        return ans == INF ? -1 : ans;
    }
};