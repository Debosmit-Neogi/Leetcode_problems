# Minimum Sum of Two Non-Overlapping Subarrays with Sum = Target

**Problem:** Given an array `arr` and an integer `target`, find two **non-overlapping** contiguous subarrays, each summing to `target`, such that the sum of their lengths is minimized. Return -1 if no such pair exists.

## Core Idea

This is a prefix-sum problem combined with dynamic programming.

1. **Finding a subarray with sum = target ending at index `i`:**
   Use a running `prefix` sum and a hash map `mp` that stores `prefix_sum -> latest_index` seen so far.
   If `prefix - target` exists in the map at index `start`, then the subarray `arr[start+1 .. i]` sums to exactly `target`, with length `i - start`.

2. **Tracking the best subarray seen so far — `best[i]`:**
   `best[i]` = the length of the **shortest** target-sum subarray fully contained within `arr[0..i]`.
   This is a running "best so far" array, carried forward:
   ```
   best[i] = best[i-1]   (default: nothing new found)
   ```
   If a new target-sum subarray ending at `i` is found (with length `len`), update:
   ```
   best[i] = min(best[i], len)
   ```

3. **Combining two non-overlapping subarrays:**
   When a target-sum subarray `[start+1, i]` is found, we want to pair it with the **best** target-sum subarray that ends **at or before `start`** (i.e., doesn't overlap it).
   That's exactly `best[start]` — the shortest target-sum subarray within `arr[0..start]`.

   So:
   ```
   ans = min(ans, len + best[start])
   ```
   This works because `best[start]` was computed using only indices `<= start`, guaranteeing no overlap with the current subarray `[start+1, i]`.

## Why This Works

- `best[]` is a **prefix-optimal** array: at any index `i`, it always holds the smallest target-sum subarray length found so far, regardless of *where* that subarray is — we only need its length and the guarantee that it lies within `[0, i]`.
- By checking `best[start]` (not `best[i]`), we ensure the second subarray we pair with strictly ends before the current one begins, satisfying the non-overlap constraint.
- Each index is processed once, and hash map operations are O(1) average, giving an overall efficient single pass.

## Step-by-Step Walkthrough

For each index `i` from `0` to `n-1`:

1. Add `arr[i]` to `prefix`.
2. Carry forward: `best[i] = best[i-1]`.
3. Check if `prefix - target` exists in `mp`:
   - If yes, let `start = mp[prefix - target]`, `len = i - start`.
   - If `start >= 0` and `best[start] != INF`, a valid non-overlapping pair exists → update `ans`.
   - Update `best[i] = min(best[i], len)` since this subarray itself might be the new shortest one ending by `i`.
4. Store `mp[prefix] = i` (always keep the **latest** index for a given prefix sum — this keeps future subarrays as short as possible).
5. At the end, return `ans` if it was updated, else `-1`.

## Complexity

- **Time:** O(n) — single pass, O(1) average hash map operations.
- **Space:** O(n) — for the `best[]` array and the prefix-sum hash map.

## Key Insight (Why It's Not Brute Force)

A naive approach would try every pair of non-overlapping target-sum subarrays — O(n²) or worse. The trick here is that we **don't need to know the identity** of the best subarray before position `start`, only its **length**. This lets `best[]` compress all the necessary history into a single running minimum, enabling an O(n) solution.

## Example

`arr = [3,2,2,4,3]`, `target = 3`

- Subarray `[3]` (index 0) → sum 3, length 1
- Subarray `[3]` (index 4) → sum 3, length 1
- These are non-overlapping → answer = 1 + 1 = **2**

The algorithm finds the second `[3]` at `i=4`, looks up `best[3]` (best subarray within `arr[0..3]`), which is 1 (from the first `[3]`), and computes `ans = min(ans, 1 + 1) = 2`.
