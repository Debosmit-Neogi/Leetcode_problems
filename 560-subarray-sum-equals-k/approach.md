# Subarray Sum Equals K — Prefix Sum + Hash Map Approach

## Problem
Given an array `nums` and an integer `k`, find the total number of contiguous subarrays whose sum equals `k`.

## Core Idea
A brute-force solution checks every subarray, which takes O(n²) time. We can do better using **prefix sums** combined with a **hash map**.

The key insight: if `prefix[j]` is the sum of all elements from index `0` to `j`, then the sum of any subarray `(i+1 ... j)` is:

```
subarraySum(i+1, j) = prefix[j] - prefix[i]
```

We want this to equal `k`, so:

```
prefix[j] - prefix[i] = k
prefix[i] = prefix[j] - k
```

So, as we scan the array and compute the running `prefix` sum at each index `j`, we just need to know **how many earlier prefix sums equal `prefix[j] - k`**. Each such earlier prefix marks the start of a valid subarray ending at `j`.

Instead of storing indices, we store the **frequency of each prefix sum seen so far** in a hash map. This lets us count all valid starting points in O(1) instead of searching for them.

## Why `mp[0] = 1`
This handles the case where a subarray starting from index `0` itself sums to `k`. If `prefix[j] == k`, then `need = prefix[j] - k = 0`. Since no actual element produced a prefix of `0` (it's the "empty prefix" before the array starts), we pre-seed the map with `mp[0] = 1` to count this case correctly.

## Step-by-Step Walkthrough

1. Initialize:
   - `mp` — hash map storing frequency of prefix sums seen so far.
   - `mp[0] = 1` — base case for subarrays starting at index 0.
   - `prefix = 0` — running sum.
   - `ans = 0` — result counter.

2. Iterate through each element `x` in `nums`:
   - Update `prefix += x`.
   - Compute `need = prefix - k` — the prefix sum we'd need to have seen earlier for a valid subarray to end here.
   - If `need` exists in `mp`, add its frequency to `ans` (each occurrence represents one valid subarray).
   - Increment `mp[prefix]` to record that this prefix sum has now been seen one more time.

3. Return `ans`.

## Dry Run Example
`nums = [1, 2, 3]`, `k = 3`

| i | x | prefix | need = prefix-k | found in mp? | ans | mp after update |
|---|---|--------|------------------|---------------|-----|------------------|
| - | - | 0      | -                | -             | 0   | {0:1}            |
| 0 | 1 | 1      | -2               | no            | 0   | {0:1, 1:1}       |
| 1 | 2 | 3      | 0                | yes (freq=1)  | 1   | {0:1, 1:1, 3:1}  |
| 2 | 3 | 6      | 3                | yes (freq=1)  | 2   | {0:1, 1:1, 3:1, 6:1} |

Result: `ans = 2` → subarrays `[3]` and `[1,2]` both sum to 3. ✅

## Complexity
- **Time:** O(n) — single pass through the array, O(1) average hash map operations.
- **Space:** O(n) — hash map can store up to n distinct prefix sums.

## Code
```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0] = 1;
        int prefix = 0;
        int ans = 0;
        for (int x : nums) {
            prefix += x;
            int need = prefix - k;
            if (mp.find(need) != mp.end()) {
                ans += mp[need];
            }
            mp[prefix]++;
        }
        return ans;
    }
};
```

## Key Takeaways
- Convert subarray-sum problems into prefix-sum difference problems.
- Use a hash map to turn an O(n) or O(n²) search into O(1) lookups.
- Always consider the "empty prefix" edge case (`mp[0] = 1`) when the target sum can be matched from the very start of the array.
