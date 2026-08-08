# LeetCode 3302 - Find the Lexicographically Smallest Valid Sequence

## Problem

We are given two strings:

```text
word1
word2
```

We need to select exactly `word2.length` indices from `word1` such that:

1. The indices are in strictly increasing order.
2. The characters selected from `word1` form a string that is **almost equal** to `word2`.
3. "Almost equal" means that we can change **at most one character** in the selected string.
4. Among all valid index sequences, return the **lexicographically smallest sequence of indices**.

If no valid sequence exists, return an empty vector.

---

# Important Observation

The most important part of this problem is:

> We want the lexicographically smallest **indices**, not the lexicographically smallest resulting string.

Therefore, we should try to select the smallest possible index at every step.

This suggests a **greedy approach**.

However, there is a problem:

Suppose the current character does not match.

We have one modification available, so we might be tempted to use the modification immediately.

But this can be wrong.

For example:

```text
word1 = "bacdc"
word2 = "abc"
```

At index `0`:

```text
word1[0] = 'b'
word2[0] = 'a'
```

We could use our one modification and choose index `0`.

That would give:

```text
[0, ...]
```

which looks lexicographically better than `[1, ...]`.

But after choosing index `0`, the remaining characters are:

```text
"ac"
```

and we need:

```text
"bc"
```

There is no way to complete the sequence with only one modification because we already used it.

Therefore, index `0` must be rejected.

The correct answer is:

```text
[1, 2, 4]
```

So we need a way to determine whether using the mismatch **now** still allows us to finish the sequence.

---

# Main Idea

We use two steps:

1. Precompute information about matching `word2` from **right to left**.
2. Build the answer greedily from **left to right**.

The right-to-left pass tells us whether the remaining suffix of `word2` can be matched exactly after a candidate index.

This allows us to safely use our one mismatch.

---

# Step 1: Reverse Matching

We create:

```cpp
vector<int> last(m, -1);
```

where:

```text
last[j]
```

stores the position in `word1` used to match `word2[j]` when matching the suffix of `word2` from right to left.

Consider:

```text
word1 = "bacdc"
         0 1 2 3 4

word2 = "abc"
         0 1 2
```

We start from the end.

For:

```text
word2[2] = 'c'
```

the rightmost matching `c` is:

```text
word1[4] = 'c'
```

so:

```text
last[2] = 4
```

Then we continue looking for:

```text
word2[1] = 'b'
```

before index `4`.

This reverse matching gives us the earliest possible positions required for the remaining suffix.

---

# Why Do We Need `last[]`?

Suppose we are currently trying to select index `i` for `word2[j]`.

If:

```text
word1[i] != word2[j]
```

then we can use our one allowed modification.

But before doing that, we must make sure that:

```text
word2[j+1...m-1]
```

can be matched **exactly** using positions after `i`.

If the next suffix requires an index that is not after `i`, then using the mismatch now is impossible.

This is checked using:

```cpp
i < last[j + 1]
```

If this condition is true, there is enough room to match the remaining suffix.

---

# Step 2: Greedy Construction

Now we scan `word1` from left to right.

We maintain:

```cpp
j
```

which represents the current character we need from `word2`.

We also maintain:

```cpp
canSkip
```

which tells us whether our one allowed mismatch is still available.

Initially:

```cpp
bool canSkip = true;
```

because we haven't used a mismatch yet.

---

# Case 1: Characters Match

Suppose:

```cpp
word1[i] == word2[j]
```

Then we can safely choose index `i`.

```cpp
ans.push_back(i);
j++;
```

There is no reason to skip this index because we want the lexicographically smallest sequence.

---

# Case 2: Characters Do Not Match

Suppose:

```cpp
word1[i] != word2[j]
```

We have two choices:

### Choice A: Skip this index

We don't select it.

Continue searching for another index.

### Choice B: Use our one modification

We can select this index and change its character.

But this is allowed only if:

1. We haven't already used our modification.
2. The remaining suffix of `word2` can be matched exactly.

The condition is:

```cpp
canSkip &&
(
    j == m - 1 ||
    i < last[j + 1]
)
```

If this is true, we choose index `i`.

Then:

```cpp
canSkip = false;
```

because we have used our one modification.

---

# Why Greedy Gives the Lexicographically Smallest Answer

At every position, we process indices in increasing order:

```cpp
for (i = 0; i < n; i++)
```

Whenever we find an index that can lead to a valid complete sequence, we immediately choose it.

Therefore, the first valid index selected for each position is the smallest possible index.

This guarantees the lexicographically smallest sequence.

---

# Complete Code

```cpp
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        /*
         * last[j] = position in word1 used to match word2[j]
         * when matching word2 from right to left.
         *
         * This helps us determine whether the remaining suffix
         * of word2 can still be matched after a candidate index.
         */
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // -------------------------------------------------------
        // STEP 1: Match word2 from RIGHT to LEFT.
        // -------------------------------------------------------

        while (i >= 0 && j >= 0) {

            if (word1[i] == word2[j]) {

                // Store the position where word2[j] is matched.
                last[j] = i;

                // Move to the previous character of word2.
                j--;
            }

            // Always move left in word1.
            i--;
        }

        // -------------------------------------------------------
        // STEP 2: Greedily construct the answer.
        // -------------------------------------------------------

        vector<int> ans;

        // j = current character of word2 we need to match.
        j = 0;

        /*
         * true  -> the one allowed modification is still available.
         * false -> we have already used the modification.
         */
        bool canSkip = true;

        // Scan word1 from left to right.
        for (i = 0; i < n; i++) {

            // We have already selected all required characters.
            if (j == m) {
                break;
            }

            // ---------------------------------------------------
            // CASE 1: Exact match
            // ---------------------------------------------------

            if (word1[i] == word2[j]) {

                /*
                 * Since this is an exact match, selecting this
                 * index does not use our modification.
                 */
                ans.push_back(i);

                j++;
            }

            // ---------------------------------------------------
            // CASE 2: Mismatch
            // ---------------------------------------------------

            else if (
                canSkip &&
                (
                    // If this is the last character of word2,
                    // there is no suffix left to worry about.
                    j == m - 1 ||

                    // Otherwise, the remaining suffix must be
                    // matchable after index i.
                    i < last[j + 1]
                )
            ) {

                /*
                 * Use our one allowed modification.
                 */
                canSkip = false;

                // Select this index.
                ans.push_back(i);

                // Move to the next character of word2.
                j++;
            }

            /*
             * Otherwise:
             *
             * - The characters mismatch.
             * - We either already used our modification,
             *   or using it now would make the suffix impossible.
             *
             * So we simply skip this index.
             */
        }

        // -------------------------------------------------------
        // STEP 3: Check whether we selected enough indices.
        // -------------------------------------------------------

        if (j == m) {
            return ans;
        }

        // Could not construct a valid sequence.
        return {};
    }
};
```

---

# Example 1

## Input

```text
word1 = "vbcca"
word2 = "abc"
```

Index representation:

```text
word1:

index:  0 1 2 3 4
char:   v b c c a
```

We need:

```text
a b c
```

The greedy algorithm chooses:

```text
index 0 -> 'v'
```

This is a mismatch, but the remaining `"bc"` can be matched.

Therefore:

```text
[0]
```

The mismatch is now used.

Next:

```text
index 1 -> 'b'
```

Exact match.

Then:

```text
index 2 -> 'c'
```

Exact match.

Result:

```text
[0,1,2]
```

---

# Example 2

## Input

```text
word1 = "bacdc"
word2 = "abc"
```

Index representation:

```text
index:  0 1 2 3 4
word1:  b a c d c
```

We need:

```text
a b c
```

---

## Position 0

We first examine index `0`:

```text
word1[0] = 'b'
word2[0] = 'a'
```

They don't match.

Could we use our one modification?

No.

If we use the modification here, we still need:

```text
b c
```

after index `0`.

That would require another mismatch, so index `0` is rejected.

---

## Position 0 - Index 1

Now:

```text
word1[1] = 'a'
word2[0] = 'a'
```

Exact match.

Choose:

```text
[1]
```

---

## Position 1

Next we need:

```text
'b'
```

Try index `2`:

```text
word1[2] = 'c'
word2[1] = 'b'
```

Mismatch.

We haven't used our modification yet.

The remaining character is:

```text
'c'
```

and it exists at:

```text
index 4
```

Therefore, we can safely use our modification here.

Choose:

```text
[1,2]
```

---

## Position 2

Now we need:

```text
'c'
```

Index `3` contains:

```text
'd'
```

This would be another mismatch, but our modification has already been used.

So we skip index `3`.

Index `4` contains:

```text
'c'
```

Choose it.

Final answer:

```text
[1,2,4]
```

---

# Example 3

## Input

```text
word1 = "aaaaaa"
word2 = "aaabc"
```

We need:

```text
a a a b c
```

There are only `a` characters in `word1`.

We can use our one modification to convert one `a` into `b`.

However, we also need:

```text
c
```

which would require a second modification.

Therefore, no valid sequence exists.

Return:

```text
[]
```

---

# Example 4

## Input

```text
word1 = "abc"
word2 = "ab"
```

We can directly select:

```text
index 0 -> 'a'
index 1 -> 'b'
```

So:

```text
[0,1]
```

---

# Complexity Analysis

Let:

```text
n = word1.length()
m = word2.length()
```

## Time Complexity

### Reverse pass

We scan `word1` once:

```text
O(n)
```

### Forward greedy pass

We scan `word1` once:

```text
O(n)
```

Therefore:

```text
Time Complexity = O(n)
```

---

## Space Complexity

We store:

```cpp
vector<int> last(m);
```

Therefore:

```text
Space Complexity = O(m)
```

This is significantly better than the previous 3D DP solution.

---

# Why the Previous DP Caused Memory Limit Exceeded

The previous solution used:

```cpp
vector<vector<vector<bool>>> can(
    n + 1,
    vector<vector<bool>>(
        m + 1,
        vector<bool>(2)
    )
);
```

This creates approximately:

```text
2 × n × m
```

states.

For large strings, this becomes enormous.

For example, if both strings have hundreds of thousands of characters:

```text
n ≈ 300,000
m ≈ 300,000
```

then:

```text
n × m
```

is approximately:

```text
90,000,000,000
```

states.

That is far beyond the available memory.

The optimized solution only stores:

```text
O(m)
```

information.

---

# Final Takeaway

The problem combines two important techniques:

## 1. Greedy

We always try to select the **smallest possible index**.

This is necessary because the answer must be lexicographically smallest by **indices**.

## 2. Reverse preprocessing

Before greedily using our one mismatch, we need to know whether the remaining suffix can still be matched.

The reverse pass provides exactly this information.

The overall strategy is:

```text
        word1
          |
          v
  Reverse preprocessing
          |
          v
  Know whether suffix is feasible
          |
          v
  Greedy left-to-right selection
          |
          v
  Lexicographically smallest answer
```

Final complexity:

```text
Time  : O(n)
Space : O(m)
```
