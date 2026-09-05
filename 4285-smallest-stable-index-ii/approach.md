# First Stable Index

## Problem

Given an array `nums` and an integer `k`, find the smallest index `i` such that the array is "stable" at `i`, defined as:

```
max(nums[0..i]) - min(nums[i..n-1]) <= k
```

That is, the maximum value in the prefix ending at `i` minus the minimum value in the suffix starting at `i` (inclusive of `i` in both) is at most `k`. Return `-1` if no such index exists.

## Approach

1. **Suffix minimum array**: Precompute `suffixMin[i] = min(nums[i], nums[i+1], ..., nums[n-1])` for every index, built right to left in O(n).
2. **Prefix maximum, computed on the fly**: Walk left to right, maintaining a running `prefixMax = max(nums[0..i])`.
3. **Check instability at each index**: At each `i`, the "instability" is `prefixMax - suffixMin[i]`. The first `i` where this is `<= k` is the answer.
4. If no index satisfies the condition, return `-1`.

This avoids recomputing min/max ranges repeatedly (which would be O(n²)) by reusing precomputed suffix minimums and an incrementally updated prefix maximum, giving O(n) time and O(n) space.

## Code (C++)

```cpp
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        // Compute minimum from i to n-1
        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        int prefixMax = nums[0];

        // Check indices from left to right
        for (int i = 0; i < n; ++i) {
            prefixMax = max(prefixMax, nums[i]);

            int instability = prefixMax - suffixMin[i];

            if (instability <= k) {
                return i;
            }
        }

        return -1;
    }
};
```

## Complexity

- **Time:** O(n) — one pass to build `suffixMin`, one pass to scan for the answer.
- **Space:** O(n) — for the `suffixMin` array (could be reduced further only if suffix values were computed differently, but O(n) is optimal here since future suffix mins are needed while scanning left to right).

## Example Walkthrough

Suppose `nums = [4, 2, 5, 1, 3]`, `k = 2`.

- `suffixMin = [1, 1, 1, 1, 3]`
- i = 0: prefixMax = 4, instability = 4 - 1 = 3 (> 2, skip)
- i = 1: prefixMax = 4, instability = 4 - 1 = 3 (> 2, skip)
- i = 2: prefixMax = 5, instability = 5 - 1 = 4 (> 2, skip)
- i = 3: prefixMax = 5, instability = 5 - 1 = 4 (> 2, skip)
- i = 4: prefixMax = 5, instability = 5 - 3 = 2 (<= 2, return 4)

Answer: `4`
