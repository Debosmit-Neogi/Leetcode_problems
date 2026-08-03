# LeetCode 1406 - Stone Game III

## Approach

We solve this problem using **Dynamic Programming (DP)**.

Instead of keeping track of Alice's and Bob's individual scores, we store the **maximum score difference** that the current player can achieve over the opponent.

### DP State

Let:

```cpp
dp[i]
```

represent the **maximum score difference (current player − opponent)** starting from index `i`.

A positive value means the current player can finish with a higher score, while a negative value means the opponent can end up with more points.

---

## Base Case

If there are no stones left to take,

```cpp
dp[n] = 0;
```

where `n` is the number of stones.

Since neither player can score any more points, the score difference is `0`.

---

## DP Transition

From each position `i`, the current player has three possible choices:

1. Take **1 stone**
2. Take **2 stones**
3. Take **3 stones**

While trying each option, we maintain the sum of the stones taken (`currSum`).

If the player takes some stones, the opponent will start playing from the next remaining position.

Since `dp[next]` represents the opponent's maximum score difference, it must be subtracted from the current player's score.

The transition becomes:

```cpp
dp[i] = max(
    take1 - dp[i + 1],
    take2 - dp[i + 2],
    take3 - dp[i + 3]
);
```

where:

- `take1` = value of taking one stone
- `take2` = value of taking two stones
- `take3` = value of taking three stones

We choose the option that gives the maximum score difference.

---

## Filling the DP Table

Since each state depends on future states (`dp[i+1]`, `dp[i+2]`, `dp[i+3]`), we compute the DP table **from right to left**.

For every index:

1. Initialize the answer with a very small value.
2. Try taking 1, 2, and 3 stones.
3. Update the maximum score difference.

---

## Determining the Winner

After filling the DP table:

- If `dp[0] > 0`, Alice can achieve a higher score.
- If `dp[0] < 0`, Bob can achieve a higher score.
- Otherwise, both players finish with the same score.

```cpp
if (dp[0] > 0)
    return "Alice";
else if (dp[0] < 0)
    return "Bob";
else
    return "Tie";
```

---

## Dry Run

**Input**

```text
stoneValue = [1, 2, 3, 7]
```

Compute from the end:

| i | Choices | dp[i] |
|---|---------|--------|
| 4 | No stones | 0 |
| 3 | Take 7 | 7 |
| 2 | Take 3 = -4, Take 3+7 = 10 | 10 |
| 1 | Best option = -2 | -2 |
| 0 | Best option = -1 | -1 |

Since:

```text
dp[0] = -1
```

Bob can achieve a score that is 1 greater than Alice.

**Answer:** `"Bob"`

---

## Complexity Analysis

### Time Complexity

For each index, we try at most **3 choices**.

```
Time Complexity = O(3 × N) = O(N)
```

### Space Complexity

We use a one-dimensional DP array of size `N + 1`.

```
Space Complexity = O(N)
```

---

## Key Idea

Instead of storing Alice's and Bob's scores separately, store the **maximum score difference** the current player can achieve.

At every position:

- Take 1, 2, or 3 stones.
- Subtract the opponent's best possible difference.
- Choose the move that maximizes the current player's advantage.

This converts the game into a simple one-dimensional DP solution.
