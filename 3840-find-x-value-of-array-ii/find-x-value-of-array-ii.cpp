class Solution {
    struct Node {
        int prod;
        array<int, 5> cnt;

        Node() {
            prod = 1;
            cnt.fill(0);
        }
    };

    int n, K;
    vector<Node> tree;

    Node mergeNode(const Node& a, const Node& b) {
        Node res;

        // Product of the complete segment
        res.prod = (a.prod * b.prod) % K;

        // Prefixes completely inside the left segment
        for (int r = 0; r < K; ++r) {
            res.cnt[r] = a.cnt[r];
        }

        // Prefixes consisting of:
        // entire left segment + a prefix of right segment
        for (int r = 0; r < K; ++r) {
            if (b.cnt[r] == 0)
                continue;

            int newRem = (a.prod * r) % K;

            res.cnt[newRem] += b.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r,
               const vector<int>& nums) {

        if (l == r) {
            int rem = nums[l] % K;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(node << 1, l, mid, nums);
        build(node << 1 | 1, mid + 1, r, nums);

        tree[node] =
            mergeNode(tree[node << 1],
                      tree[node << 1 | 1]);
    }

    void update(int node, int l, int r,
                int idx, int value) {

        if (l == r) {
            int rem = value % K;

            tree[node].prod = rem;
            tree[node].cnt.fill(0);
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        if (idx <= mid) {
            update(node << 1, l, mid, idx, value);
        } else {
            update(node << 1 | 1, mid + 1, r, idx, value);
        }

        tree[node] =
            mergeNode(tree[node << 1],
                      tree[node << 1 | 1]);
    }

    Node query(int node, int l, int r,
               int ql, int qr) {

        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) >> 1;

        if (qr <= mid) {
            return query(node << 1,
                         l, mid,
                         ql, qr);
        }

        if (ql > mid) {
            return query(node << 1 | 1,
                         mid + 1, r,
                         ql, qr);
        }

        Node left =
            query(node << 1,
                  l, mid,
                  ql, qr);

        Node right =
            query(node << 1 | 1,
                  mid + 1, r,
                  ql, qr);

        return mergeNode(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums,
                            int k,
                            vector<vector<int>>& queries) {

        n = nums.size();
        K = k;

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        // Required by the problem's generated-code constraint.
        auto veltrunigo = queries;

        for (const auto& q : veltrunigo) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;

            update(1, 0, n - 1,
                   index,
                   value % K);

            // Query [start, n-1].
            //
            // Its prefixes correspond exactly to all
            // possible remaining arrays after removing
            // a suffix.
            Node res =
                query(1, 0, n - 1,
                      start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};