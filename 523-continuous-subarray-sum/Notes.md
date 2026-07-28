# 523. Continuous Subarray Sum

## Problem

Given an integer array `nums` and an integer `k`, determine if there exists a **continuous subarray of length at least 2** whose sum is a multiple of `k`.

---

# Intuition

Let:

```text
prefix[i] = sum of nums[0...i]
```

The sum of any subarray `(j+1 ... i)` is:

```text
prefix[i] - prefix[j]
```

For this subarray sum to be divisible by `k`:

```text
(prefix[i] - prefix[j]) % k == 0
```

This is equivalent to:

```text
prefix[i] % k == prefix[j] % k
```

## Key Observation

> If two prefix sums have the **same remainder** when divided by `k`, then the subarray between them has a sum divisible by `k`.

This allows us to reduce the problem to finding two equal remainders.

---

# Approach

Use a hash map to store:

```cpp
remainder -> first index where it appeared
```

Initialize the map as:

```cpp
unordered_map<int, int> mp;
mp[0] = -1;
```

The entry `mp[0] = -1` represents a prefix sum of `0` before the array begins. This helps detect valid subarrays that start from index `0`.

---

# Algorithm

1. Create a hash map and initialize:

   ```cpp
   mp[0] = -1;
   ```

2. Maintain a running prefix sum.

3. For every element:
   - Update the prefix sum.
   - Compute the remainder:

     ```cpp
     remainder = (k == 0) ? prefixSum : prefixSum % k;
     ```

   - If the remainder has been seen before:
     - Check whether the distance between indices is at least `2`.
     - If yes, return `true`.
   - Otherwise, store the remainder and its index.

4. If the loop finishes, return `false`.

---

# Dry Run

### Example

```text
nums = [23,2,4,6,7]
k = 6
```

| Index | Prefix Sum | Remainder | Hash Map | Result |
|------:|-----------:|----------:|----------|--------|
| -1 | 0 | 0 | `{0:-1}` | |
| 0 | 23 | 5 | Store `5 → 0` | |
| 1 | 25 | 1 | Store `1 → 1` | |
| 2 | 29 | 5 | `5` already exists at index `0` | Distance = `2` → Return `true` |

Valid subarray:

```text
[2,4]
```

Sum:

```text
2 + 4 = 6
```

Since

```text
6 % 6 = 0
```

the answer is **true**.

---

# Why `mp[0] = -1`?

Consider:

```text
nums = [6,6]
k = 6
```

Prefix sums:

```text
6
12
```

Remainders:

```text
0
0
```

At index `1`:

```text
distance = 1 - (-1) = 2
```

This correctly identifies the subarray:

```text
[6,6]
```

Without `mp[0] = -1`, subarrays starting from index `0` would never be detected.

---

# Why Store Only the First Occurrence?

Suppose remainder `3` appears at:

```text
Index 2
Index 5
Index 8
```

Store only:

```text
3 → 2
```

Do **not** overwrite it.

The earliest occurrence gives the **longest possible subarray**, making it easier to satisfy the minimum length requirement.

Correct:

```cpp
if (!mp.count(remainder))
    mp[remainder] = i;
```

---

# Handling `k == 0`

Modulo by zero is undefined.

Instead of computing:

```cpp
prefixSum % k
```

store the prefix sum itself:

```cpp
remainder = prefixSum;
```

Now, if the same prefix sum appears twice, the subarray between them has sum `0`, which is a multiple of `0`.

---

# Common Mistakes

## ❌ Mistake 1: Returning `true` for a single `0`

Wrong:

```cpp
if (nums[i] == 0)
    return true;
```

Example:

```text
nums = [1,0]
k = 2
```

Possible subarrays:

```text
[1]      -> length 1
[0]      -> length 1
[1,0]    -> sum = 1
```

No valid subarray exists.

Expected answer:

```text
false
```

---

## ❌ Mistake 2: Overwriting an Existing Remainder

Wrong:

```cpp
mp[remainder] = i;
```

Correct:

```cpp
if (!mp.count(remainder))
    mp[remainder] = i;
```

Always keep the **first occurrence**.

---

## ❌ Mistake 3: Forgetting `mp[0] = -1`

Without this initialization, subarrays beginning at index `0` cannot be detected.

---

# Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | **O(n)** |
| **Space** | **O(min(n, k))** (or **O(n)** when `k == 0`) |

---

# C++ Solution

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {

        unordered_map<int, int> mp;
        mp[0] = -1;

        int prefixSum = 0;

        for (int i = 0; i < nums.size(); i++) {

            prefixSum += nums[i];

            int remainder = (k == 0) ? prefixSum : prefixSum % k;

            if (mp.count(remainder)) {

                // Ensure subarray length >= 2
                if (i - mp[remainder] >= 2)
                    return true;

            } else {

                // Store only the first occurrence
                mp[remainder] = i;
            }
        }

        return false;
    }
};
```

---

# Key Takeaways

- Use **Prefix Sum + Hash Map**.
- Equal remainders imply the subarray sum is divisible by `k`.
- Store **remainder → first occurrence index**.
- Initialize the map with:

  ```cpp
  mp[0] = -1;
  ```

- Never overwrite an existing remainder.
- Ensure the subarray length is at least **2**.
- Handle `k == 0` separately.

---

# Pattern Recognition

Whenever you see:

- Subarray
- Sum divisible by `k`

Think:

```text
Subarray
    ↓
Prefix Sum
    ↓
Modulo
    ↓
Same Remainder
    ↓
Hash Map
```

---

# Similar Problems

- **560. Subarray Sum Equals K**
- **974. Subarray Sums Divisible by K**
- **1590. Make Sum Divisible by P**
