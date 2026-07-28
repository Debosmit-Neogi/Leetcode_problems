<h2>continuous-subarray-sum Notes</h2><hr>[ Time taken: 2d 22hrs 12m 43s ]

523. Continuous Subarray Sum — Quick Notes
Idea: Use Prefix Sum + Hash Map.
A subarray sum is:
prefix[i] - prefix[j]
It is divisible by k when:
(prefix[i] - prefix[j]) % k == 0

which implies

prefix[i] % k == prefix[j] % k

Same remainder ⇒ subarray sum is divisible by k.

Store in a hash map:
remainder -> first index where it appeared
Initialize:
mp[0] = -1;

This handles subarrays starting from index 0.

For every element:
prefixSum += nums[i];
remainder = (k == 0) ? prefixSum : prefixSum % k;
If the remainder already exists:
if (i - mp[remainder] >= 2)
    return true;
Otherwise, store the first occurrence:
if (!mp.count(remainder))
    mp[remainder] = i;
Do not overwrite an existing remainder.
Do not return true for a single 0; the subarray length must be at least 2.
Special case: If k == 0, compare prefix sums instead of taking modulo.
Complexity:
Time: O(n)
Space: O(min(n, k)) (or O(n) if k == 0)
Pattern to Remember
Subarray
    ↓
Prefix Sum
    ↓
Modulo k
    ↓
Same Remainder
    ↓
Hash Map
