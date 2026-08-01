# LeetCode 486 - Predict the Winner
# LeetCode 486 - Predict the Winner

## Problem

Two players take turns picking a number from either the **left** or the **right** end of the array.

- Player 1 starts first.
- Both players play **optimally**.
- Return `true` if Player 1 can win (or tie).

---

# Intuition

Since both players play optimally, whenever it is our turn, we want to choose the move that gives us the maximum possible advantage over the opponent.

Instead of keeping track of both players' scores separately, we track only the **score difference**.

### Definition

Let

```
dp[i][j]
```

be the **maximum score difference** (Current Player − Opponent) that the current player can achieve using the subarray

```
nums[i...j]
```

If this value is positive, the current player scores more.

If it is negative, the opponent scores more.

---

# Recurrence

Suppose we are considering the subarray

```
nums[i...j]
```

We have two choices.

## Choice 1: Pick the left element

We gain

```
nums[i]
```

Now the opponent becomes the current player for

```
(i+1, j)
```

The opponent can achieve a score difference of

```
dp[i+1][j]
```

Since this advantage belongs to the opponent, our final advantage becomes

```
nums[i] - dp[i+1][j]
```

---

## Choice 2: Pick the right element

Similarly,

```
nums[j] - dp[i][j-1]
```

---

## Transition

Therefore,

```
dp[i][j] =
max(
    nums[i] - dp[i+1][j],
    nums[j] - dp[i][j-1]
)
```

---

# Base Case

When only one number remains,

```
i == j
```

the current player simply takes that number.

```
dp[i][i] = nums[i]
```

---

# Why Does Subtraction Work?

This is the most important idea.

Suppose we pick the left element.

Our score immediately increases by

```
nums[i]
```

Now the opponent starts playing on

```
(i+1, j)
```

The value

```
dp[i+1][j]
```

represents

```
Opponent Score − Our Score
```

for the remaining game.

Therefore our overall advantage becomes

```
nums[i] - dp[i+1][j]
```

The subtraction converts the opponent's advantage into our perspective.

---

# Example

Consider

```
nums = [1,5,2]
```

### Base cases

```
dp[0][0] = 1
dp[1][1] = 5
dp[2][2] = 2
```

Table

```
1 5 2
```

---

### Length = 2

For

```
[1,5]
```

```
takeLeft = 1 - 5 = -4

takeRight = 5 - 1 = 4

dp[0][1] = 4
```

For

```
[5,2]
```

```
takeLeft = 5 - 2 = 3

takeRight = 2 - 5 = -3

dp[1][2] = 3
```

Current DP table

```
1 4
  5 3
    2
```

---

### Length = 3

For

```
[1,5,2]
```

```
takeLeft = 1 - dp[1][2]
         = 1 - 3
         = -2

takeRight = 2 - dp[0][1]
          = 2 - 4
          = -2

dp[0][2] = -2
```

Since

```
dp[0][2] < 0
```

Player 1 loses.

Answer:

```
false
```

---

# Algorithm

1. Create an `n × n` DP table.
2. Fill the diagonal with `nums[i]`.
3. Compute answers for subarrays of length `2` to `n`.
4. Return

```
dp[0][n-1] >= 0
```

---

# C++ Solution

```cpp
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case
        for (int i = 0; i < n; i++)
            dp[i][i] = nums[i];

        // Fill DP table
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {

                int j = i + len - 1;

                int takeLeft = nums[i] - dp[i + 1][j];
                int takeRight = nums[j] - dp[i][j - 1];

                dp[i][j] = max(takeLeft, takeRight);
            }
        }

        return dp[0][n - 1] >= 0;
    }
};
```

---

# Complexity Analysis

### Time Complexity

There are

```
n × n
```

states.

Each state takes

```
O(1)
```

time.

Therefore,

```
Time = O(n²)
```

---

### Space Complexity

The DP table contains

```
n × n
```

entries.

```
Space = O(n²)
```

---

# Key Takeaways

- This is a classic **Game Theory + Dynamic Programming** problem.
- Instead of storing individual scores, store the **maximum score difference**.
- At every step:
  - Pick left
  - Pick right
  - Choose the better option
- The recurrence is

```
dp[i][j] =
max(
    nums[i] - dp[i+1][j],
    nums[j] - dp[i][j-1]
)
```

- If the final score difference is non-negative,

```
dp[0][n-1] >= 0
```

Player 1 can guarantee at least a tie, which counts as a win.
