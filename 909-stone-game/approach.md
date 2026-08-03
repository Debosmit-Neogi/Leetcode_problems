# LeetCode 877 - Stone Game

## Approach

We solve this problem using **Dynamic Programming (DP)**.

Instead of tracking the individual scores of Alice and Bob, we store the **maximum score difference** that the current player can achieve over the opponent for every subarray of piles.

---

## DP State

Let

```cpp
dp[i][j]
```

represent the **maximum score difference (current player − opponent)** that the current player can obtain from the subarray `piles[i...j]`.

- A positive value means the current player can finish with more stones than the opponent.
- A negative value means the opponent can end up with more stones.
- A value of `0` means both players collect the same number of stones from that subarray.

---

## Base Case

If there is only one pile left (`i == j`), the current player simply takes that pile.

```cpp
dp[i][i] = piles[i];
```

Since the opponent gets nothing, the score difference equals the number of stones in that pile.

---

## DP Transition

For every subarray `piles[i...j]`, the current player has two choices:

### Option 1: Take the left pile

The player gains `piles[i]` stones.

The opponent then plays optimally on the remaining subarray `piles[i+1...j]`.

Since `dp[i+1][j]` represents the opponent's score difference, we subtract it from our current gain.

```cpp
takeLeft = piles[i] - dp[i + 1][j];
```

---

### Option 2: Take the right pile

Similarly, if the player chooses the last pile,

```cpp
takeRight = piles[j] - dp[i][j - 1];
```

---

### Choose the Best Move

The current player always chooses the move that maximizes their score difference.

```cpp
dp[i][j] = max(takeLeft, takeRight);
```

---

## Filling the DP Table

Each state depends on:

- `dp[i+1][j]`
- `dp[i][j-1]`

These states correspond to **smaller subarrays**.

Therefore, we compute the DP table by increasing the subarray length from `2` to `n`.

```cpp
for (int len = 2; len <= n; len++) {
    ...
}
```

This ensures all required smaller subproblems have already been solved.

---

## Determining the Winner

After filling the DP table,

```cpp
dp[0][n-1]
```

represents the maximum score difference Alice can achieve over Bob for the entire array.

- If `dp[0][n-1] > 0`, Alice collects more stones.
- Otherwise, Bob collects more stones (or ties, though the problem guarantees no ties).

```cpp
return dp[0][n-1] > 0;
```

---

## Dry Run

### Input

```text
piles = [5, 3, 4, 5]
```

### Base Cases

| Subarray | DP Value |
|----------|---------:|
| [5] | 5 |
| [3] | 3 |
| [4] | 4 |
| [5] | 5 |

---

### Length = 2

| Subarray | Calculation | DP |
|----------|-------------|---:|
| [5,3] | max(5−3, 3−5) | 2 |
| [3,4] | max(3−4, 4−3) | 1 |
| [4,5] | max(4−5, 5−4) | 1 |

---

### Length = 3

| Subarray | Calculation | DP |
|----------|-------------|---:|
| [5,3,4] | max(5−1, 4−2) | 4 |
| [3,4,5] | max(3−1, 5−1) | 4 |

---

### Length = 4

| Subarray | Calculation | DP |
|----------|-------------|---:|
| [5,3,4,5] | max(5−4, 5−4) | 1 |

Final result:

```text
dp[0][3] = 1
```

Since the score difference is positive,

**Answer:** `true`

---

## Complexity Analysis

### Time Complexity

There are `O(n²)` DP states, and each state is computed in constant time.

```
Time Complexity = O(n²)
```

---

### Space Complexity

We store an `n × n` DP table.

```
Space Complexity = O(n²)
```

---

## Key Idea

Instead of calculating Alice's and Bob's scores separately, compute the **maximum score difference** the current player can achieve for every subarray.

For each state:

- Take the left pile or the right pile.
- Subtract the opponent's best possible score difference.
- Choose the option that gives the maximum advantage.

This transforms the game into a classic interval DP problem.
