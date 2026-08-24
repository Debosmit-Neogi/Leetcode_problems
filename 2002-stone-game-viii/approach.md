# Stone Game VIII — Solution Approach

## 1. Key Observation

After a move, the first stone is replaced by the sum of a prefix of the current row.

For example:

```text
stones = [-1, 2, -3, 4, -5]
```

Prefix sums are:

```text
[-1, 1, -2, 2, -3]
```

If we remove the first four stones:

```text
[-1, 2, -3, 4]
```

their sum is `2`, so the row becomes:

```text
[2, -5]
```

Thus, the game can be represented using prefix sums rather than individual stones.

---

## 2. Prefix Sum

Define:

```text
prefix[i] = stones[0] + ... + stones[i]
```

For:

```text
stones = [-1, 2, -3, 4, -5]
```

we get:

```text
prefix = [-1, 1, -2, 2, -3]
```

Every possible first move corresponds to choosing one of these prefix sums.

---

## 3. DP Idea

Let `dp` represent the best score difference the current player can obtain from the remaining game.

If the current player chooses `prefix[i]`:

- They gain `prefix[i]`.
- The opponent then plays optimally.
- If the opponent can obtain a difference of `dp`, that becomes a disadvantage for the current player.

Therefore:

```text
new difference = prefix[i] - dp
```

We choose the better of:

```text
dp
```

and:

```text
prefix[i] - dp
```

So the recurrence is:

```text
dp = max(dp, prefix[i] - dp)
```

---

## 4. Base Case

The correct starting value is the sum of the entire array:

```text
dp = prefix[n - 1]
```

This is important. The base case should **not** be `prefix[n - 2]`.

Then we consider smaller valid prefixes by iterating backwards.

Because the rules require `x > 1`, the smallest valid prefix index is `1`.

Therefore:

```text
for i = n - 2 down to 1
```

---

## 5. Complete C++ Solution

```cpp
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {

        int n = stones.size();

        // Build prefix sums
        vector<int> prefix(n);

        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        // Base case: total sum
        int dp = prefix[n - 1];

        // Consider smaller prefix sums
        for (int i = n - 2; i >= 1; i--) {

            // Current player gets prefix[i].
            // The opponent then gets dp.
            dp = max(
                dp,
                prefix[i] - dp
            );
        }

        return dp;
    }
};
```

---

## 6. Dry Run

Consider:

```text
stones = [-1, 2, -3, 4, -5]
```

Prefix sums:

```text
prefix = [-1, 1, -2, 2, -3]
```

Start:

```text
dp = prefix[4]
   = -3
```

### `i = 3`

```text
prefix[3] = 2

prefix[3] - dp
= 2 - (-3)
= 5
```

Therefore:

```text
dp = max(-3, 5)
   = 5
```

### `i = 2`

```text
prefix[2] = -2

-2 - 5 = -7

dp = max(5, -7)
   = 5
```

### `i = 1`

```text
prefix[1] = 1

1 - 5 = -4

dp = max(5, -4)
   = 5
```

Final answer:

```text
5
```

---

## 7. Understanding the Optimal Play

For:

```text
stones = [-1, 2, -3, 4, -5]
```

Alice can remove:

```text
[-1, 2, -3, 4]
```

The sum is:

```text
2
```

Alice gets `+2`.

The remaining row is:

```text
[2, -5]
```

Bob removes both stones, getting:

```text
2 + (-5) = -3
```

Therefore:

```text
Alice - Bob
= 2 - (-3)
= 5
```

So the optimal answer is:

```text
5
```

---

## 8. Why the Recurrence Works

Suppose the current player chooses a prefix whose sum is:

```text
prefix[i]
```

The current player gains:

```text
prefix[i]
```

The opponent gets the next turn.

If the opponent's best achievable score difference is:

```text
dp
```

then from the current player's perspective that becomes:

```text
-prefix[i]
```

more precisely, the resulting difference is:

```text
prefix[i] - dp
```

Therefore we maximize:

```text
dp = max(dp, prefix[i] - dp)
```

This automatically handles both Alice's maximizing strategy and Bob's minimizing strategy.

---

## 9. Why We Iterate Backwards

The recurrence for a smaller prefix depends on the answer for a larger prefix.

So we start from:

```text
prefix[n - 1]
```

and move backwards:

```text
n - 2
n - 3
...
1
```

This allows the current `dp` to represent the already-computed result for the next state.

---

## 10. Complexity

Building the prefix sums:

```text
O(n)
```

Backward DP:

```text
O(n)
```

Therefore:

```text
Time Complexity:  O(n)
Space Complexity: O(n)
```

The DP itself only uses one variable, so the additional DP space is `O(1)`.

---

## 11. Core Pattern

The entire solution can be remembered as:

```text
Build prefix sums

dp = prefix[n - 1]

for i = n - 2 down to 1:
    dp = max(dp, prefix[i] - dp)

return dp
```

### Main insight

> Every move replaces a prefix of the row with its sum, so the game can be reduced to choosing among prefix sums.

### Game-theory insight

> If the current player gains `prefix[i]` and the opponent can achieve `dp`, the current player's resulting score difference is `prefix[i] - dp`.

This gives the compact recurrence:

```text
dp = max(dp, prefix[i] - dp)
```
