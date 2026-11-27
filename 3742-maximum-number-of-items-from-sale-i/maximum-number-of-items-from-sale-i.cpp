class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int maxF = 0, pm = INT_MAX;
        for (auto& it : items) {
            maxF = max(maxF, it[0]);
            pm = min(pm, it[1]);
        }

        // g[i] = number of other items whose factor is a multiple of items[i][0]
        vector<int> g(n, 0);
        if (maxF <= 2000000) {
            vector<int> cnt(maxF + 1, 0);
            for (auto& it : items) cnt[it[0]]++;
            vector<int> mult(maxF + 1, 0); // mult[f] = # items with factor multiple of f
            for (int f = 1; f <= maxF; f++) {
                if (!cnt[f] && false) continue;
                int s = 0;
                for (int m = f; m <= maxF; m += f) s += cnt[m];
                mult[f] = s;
            }
            for (int i = 0; i < n; i++) g[i] = mult[items[i][0]] - 1;
        } else {
            for (int i = 0; i < n; i++) {
                int c = 0;
                for (int j = 0; j < n; j++)
                    if (j != i && items[j][0] % items[i][0] == 0) c++;
                g[i] = c;
            }
        }

        // 0/1 knapsack: first copy of item i costs price, gives 1 + g[i]
        vector<long long> dp(budget + 1, 0);
        for (int i = 0; i < n; i++) {
            int p = items[i][1];
            long long v = 1 + g[i];
            for (int b = budget; b >= p; b--)
                dp[b] = max(dp[b], dp[b - p] + v);
        }

        long long ans = 0;
        for (int b = 0; b <= budget; b++)
            ans = max(ans, dp[b] + (long long)(budget - b) / pm);
        return (int)ans;
    }
};