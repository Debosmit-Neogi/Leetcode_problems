class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;
        long long v = val % MOD;

        tree[node].sq = (
            tree[node].sq
            + 2LL * v % MOD * tree[node].sum % MOD
            + v * v % MOD * len % MOD
        ) % MOD;

        tree[node].sum = (
            tree[node].sum + v * len
        ) % MOD;

        tree[node].lazy = (tree[node].lazy + v) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    void pull(int node) {
        tree[node].sum = (
            tree[node * 2].sum + tree[node * 2 + 1].sum
        ) % MOD;

        tree[node].sq = (
            tree[node * 2].sq + tree[node * 2 + 1].sq
        ) % MOD;
    }

    void update(int node, int l, int r,
                int ql, int qr, long long val) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        pull(node);
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());

        unordered_map<int, int> last;
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int prev = -1;

            if (last.count(nums[r]))
                prev = last[nums[r]];

            // Distinct counts increase by 1 for these starts.
            update(1, 0, n - 1, prev + 1, r, 1);

            last[nums[r]] = r;

            // Sum of squared distinct counts for subarrays
            // ending at r.
            ans = (ans + tree[1].sq) % MOD;
        }

        return ans;
    }
};