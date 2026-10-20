
class Solution {
    bool isRotation(vector<int>& nums, vector<int>& sorted,
                    int start, int k) {
        // KMP prefix function for the sorted block
        vector<int> pi(k, 0);

        for (int i = 1; i < k; i++) {
            int j = pi[i - 1];

            while (j > 0 && sorted[start + i] != sorted[start + j])
                j = pi[j - 1];

            if (sorted[start + i] == sorted[start + j])
                j++;

            pi[i] = j;
        }

        // Search the sorted block in the circular original block.
        // A rotation appears in the first 2*k - 1 elements.
        int j = 0;

        for (int t = 0; t < 2 * k - 1; t++) {
            int x = nums[start + (t % k)];

            while (j > 0 && x != sorted[start + j])
                j = pi[j - 1];

            if (x == sorted[start + j])
                j++;

            if (j == k)
                return true;
        }

        return false;
    }

public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool ok = true;

            for (int start = 0; start < n; start += k) {
                if (!isRotation(nums, sorted, start, k)) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                ans += k;
        }

        return ans;
    }
};
