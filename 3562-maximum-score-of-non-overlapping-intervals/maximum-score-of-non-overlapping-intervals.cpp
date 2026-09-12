
class Solution {
public:
    struct State {
        long long score;
        vector<int> ids;
    };

    bool lexicographicallySmaller(const vector<int>& a,
                                  const vector<int>& b) {
        return lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end()
        );
    }

    State better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score ? a : b;

        if (lexicographicallySmaller(a.ids, b.ids))
            return a;

        return b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store:
        // [left, right, weight, original_index]
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by left endpoint.
        sort(a.begin(), a.end(),
             [](const auto& x, const auto& y) {
                 if (x[0] != y[0])
                     return x[0] < y[0];

                 if (x[1] != y[1])
                     return x[1] < y[1];

                 return x[3] < y[3];
             });

        // Store all left endpoints.
        vector<long long> starts(n);

        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        // next[i] = first interval whose left endpoint
        // is strictly greater than a[i].right.
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            next[i] =
                upper_bound(
                    starts.begin(),
                    starts.end(),
                    a[i][1]
                ) - starts.begin();
        }

        // dp[i][k]:
        // Best result using intervals [i ... n-1],
        // choosing at most k intervals.
        vector<vector<State>> dp(
            n + 1,
            vector<State>(5)
        );

        // Base case: choose nothing.
        for (int i = 0; i <= n; i++) {
            for (int k = 0; k <= 4; k++) {
                dp[i][k].score = 0;
                dp[i][k].ids.clear();
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                // -------------------------
                // Option 1: Skip interval i
                // -------------------------
                State skip = dp[i + 1][k];

                // -------------------------
                // Option 2: Take interval i
                // -------------------------
                State take;

                take.score =
                    a[i][2] +
                    dp[next[i]][k - 1].score;

                take.ids = dp[next[i]][k - 1].ids;

                // Add original index.
                take.ids.push_back((int)a[i][3]);

                // The DP processes intervals by left endpoint,
                // so sort the final <=4 indices for lexicographic
                // comparison.
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(skip, take);
            }
        }

        return dp[0][4].ids;
    }
};
