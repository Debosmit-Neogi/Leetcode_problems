class Solution {
public:
    multiset<int> low, high;
    long long sumLow = 0, sumHigh = 0;

    void add(int num) {
        if (low.empty() || num <= *low.rbegin()) {
            low.insert(num);
            sumLow += num;
        } else {
            high.insert(num);
            sumHigh += num;
        }

        balance();
    }

    void remove(int num) {
        auto it = low.find(num);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= num;
        } else {
            it = high.find(num);
            high.erase(it);
            sumHigh -= num;
        }

        balance();
    }

    void balance() {
        int target = (low.size() + high.size() + 1) / 2;

        while (low.size() > target) {
            auto it = prev(low.end());
            int val = *it;

            low.erase(it);
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < target) {
            auto it = high.begin();
            int val = *it;

            high.erase(it);
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    long long getCost() {
        long long median = *low.rbegin();

        long long leftCost =
            median * (long long)low.size() - sumLow;

        long long rightCost =
            sumHigh - median * (long long)high.size();

        return leftCost + rightCost;
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        if (k == 0) return 0;

        vector<long long> cost(n - x + 1);

        // Initialize first window
        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        // Sliding window
        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            cost[i - x + 1] = getCost();
        }

        // DP with rolling arrays
        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current element
                curr[i] = curr[i - 1];

                // Select window ending at i-1
                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};