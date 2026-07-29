# Longest Common Subsequence (LCS) - Approach

## Problem Statement

Given two strings `text1` and `text2`, find the length of their **Longest Common Subsequence (LCS)**.

> A **subsequence** is a sequence that appears in the same relative order but **does not need to be contiguous**.

### Example

```
text1 = "abcde"
text2 = "ace"

Longest Common Subsequence = "ace"
Length = 3
```

---

# Key Observation

Unlike a substring, a subsequence allows us to **skip characters**.

This means:

- If the current characters match, we include them in the subsequence.
- If they do not match, we try skipping one character from either string and keep the better result.

---

# DP State

Let

```
dp[i][j]
```

represent:

> Length of the **Longest Common Subsequence** between

- the first `i` characters of `text1`
- the first `j` characters of `text2`

The extra row and column represent empty strings.

---

# DP Transition

## Case 1 : Characters Match

If

```
text1[i-1] == text2[j-1]
```

then the current character is part of the LCS.

Therefore,

```
dp[i][j] = 1 + dp[i-1][j-1]
```

### Why?

Since both characters are the same, we include them in the subsequence and continue solving for the remaining prefixes.

Example

```
text1 = "abc"
text2 = "adc"

Current characters = 'c' and 'c'

Previous LCS = "a"

New LCS = "ac"

Length = 1 + previous answer
```

---

## Case 2 : Characters Do Not Match

If

```
text1[i-1] != text2[j-1]
```

then at least one of these characters cannot belong to the final LCS.

We have two choices:

1. Ignore the current character of `text1`

```
dp[i-1][j]
```

2. Ignore the current character of `text2`

```
dp[i][j-1]
```

Take the better of the two.

```
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

---

# Why Do We Take Maximum?

Suppose

```
text1 = "abc"
text2 = "adc"
```

We compare

```
'b' and 'd'
```

They do not match.

Since subsequences can skip characters,

we try

- Skip `'b'`
- Skip `'d'`

Whichever gives the longer subsequence becomes the answer.

This is why we write

```
dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

---

# DP Initialization

Create a DP table of size

```
(n+1) × (m+1)
```

Initialize every value to **0**.

The first row and first column represent comparisons with an empty string.

Since the LCS with an empty string is always empty,

```
dp[0][j] = 0
dp[i][0] = 0
```

---

# Computing the Answer

Fill the DP table row by row using the transition.

The final answer is stored in

```
dp[n][m]
```

because it represents the LCS of the complete strings.

---

# Algorithm

1. Create a DP table of size `(n+1) × (m+1)` initialized to `0`.
2. Traverse both strings.
3. If the characters match, move diagonally and add `1`.
4. Otherwise, take the maximum of the top and left cells.
5. Return `dp[n][m]`.

---

# Complexity Analysis

### Time Complexity

```
O(n × m)
```

Each pair of characters is processed exactly once.

### Space Complexity

```
O(n × m)
```

Can be optimized to

```
O(m)
```

using two 1D arrays.

---

# Example

```
text1 = "abcde"
text2 = "ace"
```

DP Table

|   | "" | a | c | e |
|---|---:|---:|---:|---:|
| "" | 0 | 0 | 0 | 0 |
| a | 0 | 1 | 1 | 1 |
| b | 0 | 1 | 1 | 1 |
| c | 0 | 1 | 2 | 2 |
| d | 0 | 1 | 2 | 2 |
| e | 0 | 1 | 2 | 3 |

Answer

```
LCS Length = 3
```

---

# Key Takeaways

- A **subsequence** does **not** need to be contiguous.
- On a match, include the character and move diagonally.
- On a mismatch, skip one character from either string and keep the better result.
- The final answer is stored in `dp[n][m]`.

---

# Difference Between LCS and Longest Common Substring

| Longest Common Subsequence | Longest Common Substring |
|----------------------------|--------------------------|
| Characters can be skipped | Characters must be contiguous |
| Mismatch → `max(top, left)` | Mismatch → `0` |
| Answer = `dp[n][m]` | Answer = Maximum value in DP table |
| State represents LCS of prefixes | State represents substring ending at `(i, j)` |
