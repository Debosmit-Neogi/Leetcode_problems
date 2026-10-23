# Approach: Sort Permutation Using Bitwise AND

## Problem Summary

You are given a permutation `nums` of the integers from `0` to `n - 1`. You may swap two elements only when their bitwise AND equals a chosen non-negative integer `k`.

Find the maximum `k` that allows the array to be sorted. If the array is already sorted, return `0`.

## Key Observation

An element at index `i` is already in its correct position if `nums[i] == i`. Otherwise, it is misplaced and must be moved through swaps.

For a swap to be allowed, both elements must contain every set bit present in `k`. Therefore, `k` must be a bitwise submask of every element that needs to move.

The largest possible `k` is the bitwise AND of all misplaced elements.

## Algorithm

1. Check whether `nums` is already sorted. If so, return `0`.
2. Initialize `k = -1`. In two's-complement integer arithmetic, this has all bits set.
3. Iterate through every index `i`:
   - If `nums[i] != i`, update `k = k & nums[i]`.
4. Return `k`.

## Example

**Input:** `nums = [0, 3, 2, 1]`

The array is not sorted. The misplaced elements are:
- Index `1`: value `3`
- Index `3`: value `1`

Compute their bitwise AND:

```text
3 = 11 (binary)
1 = 01 (binary)
---------
1 = 01 (binary)
```

So the answer is `1`.

With `k = 1`, the values `3` and `1` can be swapped because `3 & 1 = 1`, producing `[0, 1, 2, 3]`.

## Complexity Analysis

- **Time complexity:** `O(n)` — the array is scanned a constant number of times.
- **Extra space complexity:** `O(1)` — only a constant amount of additional memory is used.

## C++ Implementation

```cpp
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();

        if (is_sorted(nums.begin(), nums.end())) {
            return 0;
        }

        int k = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                k &= nums[i];
            }
        }

        return k;
    }
};
```
