# 1140. Stone Game II

## Problem

Alice and Bob are playing a game with a row of stone piles.

Each pile contains a positive number of stones:

```text
piles[i]
```

They take turns, with **Alice going first**.

There is a variable `M`:

* Initially, `M = 1`
* On each turn, a player can take the first `X` remaining piles
* `1 <= X <= 2 * M`
* After taking `X` piles:

```text
M = max(M, X)
```

The game continues until all piles are taken.

Both Alice and Bob play optimally.

We need to return:

> **The maximum number of stones Alice can obtain.**

---

# Example

```text
Input:
piles = [2,7,9,4,4]

Output:
10
```

Alice can obtain a maximum of `10` stones when both players play optimally.

---

# 1. Understanding the Game

Initially:

```text
M = 1
```

Therefore Alice can take:

```text
1 <= X <= 2
```

piles.

If Alice takes `X = 1`:

```text
M = max(1, 1)
  = 1
```

If Alice takes `X = 2`:

```text
M = max(1, 2)
  = 2
```

Now Bob can take up to:

```text
2 * M
= 2 * 2
= 4
```

piles.

Therefore, every decision affects the future because it changes `M`.

This makes a greedy solution difficult.

For example, simply taking the largest possible number of piles is not necessarily optimal.

We need **Dynamic Programming**.

---

# 2. Why Greedy Does Not Work

Suppose we always try to take the maximum number of piles.

That might seem reasonable because taking more stones now is good.

However, taking more piles also increases `M`.

A larger `M` gives the opponent more freedom on their next turn.

For example:

```text
M = 1
```

If we take:

```text
X = 2
```

then:

```text
M = 2
```

and the opponent can take up to:

```text
2 * M = 4
```

piles.

Therefore, sometimes taking fewer piles now can force a better situation later.

Since both players play optimally, we need to consider all possible choices.

---

# 3. Minimax Thinking

This is a two-player game.

Both players are trying to maximize the number of stones they receive.

Suppose it is currently our turn.

We have several possible choices:

```text
Take 1 pile
Take 2 piles
Take 3 piles
...
Take 2*M piles
```

For every choice, the opponent will also play optimally.

Therefore:

```text
My best result
    =
maximum result among all possible moves
```

But what happens after I make a move?

It becomes the opponent's turn.

The opponent will try to maximize **their** number of stones.

This leads to an important observation:

> Instead of separately calculating Alice's and Bob's scores, we can define our DP from the perspective of the player whose turn it currently is.

---

# 4. DP State

Define:

```cpp
solve(i, M)
```

as:

> The maximum number of stones the **current player** can obtain from pile `i` onward when the current value of `M` is `M`.

So our state has two variables:

```text
i = index of the first remaining pile
M = current maximum-pile parameter
```

Therefore:

```text
DP State = (i, M)
```

---

# 5. Example of a DP State

Consider:

```text
piles = [2,7,9,4,4]
```

Suppose:

```text
i = 1
M = 2
```

Then the remaining piles are:

```text
7  9  4  4
^
i
```

The current player can take:

```text
X = 1, 2, 3, 4
```

because:

```text
1 <= X <= 2*M
1 <= X <= 4
```

For each choice, we calculate what happens afterward.

---

# 6. The Important Trick

Suppose there are:

```text
suffix[i]
```

total stones remaining.

If we make a particular move and then let the opponent play optimally, suppose the opponent can eventually obtain:

```text
opponent
```

stones.

Then we will receive:

```text
suffix[i] - opponent
```

stones.

Why?

Because all remaining stones eventually belong to either:

```text
Current player
+
Opponent
```

Therefore:

```text
Current player's stones
=
Total remaining stones
-
Opponent's stones
```

This is the key idea behind the solution.

---

# 7. Recurrence

Suppose we are at:

```text
solve(i, M)
```

We choose to take `X` piles.

The number of piles we can take is:

```text
1 <= X <= 2*M
```

After taking `X` piles:

```text
new index = i + X
```

And:

```text
new M = max(M, X)
```

Now it is the opponent's turn.

Therefore the opponent can obtain:

```cpp
solve(i + X, max(M, X))
```

stones.

The total number of stones currently remaining is:

```cpp
suffix[i]
```

Therefore, if we choose `X`, our result is:

```cpp
suffix[i] - solve(i + X, max(M, X))
```

We try every possible `X` and choose the maximum.

So the recurrence is:

```text
solve(i, M)
=
max(
    suffix[i] - solve(i + X, max(M, X))
)
```

for:

```text
1 <= X <= 2*M
```

---

# 8. Why Do We Subtract the Opponent?

This is worth understanding carefully.

Imagine:

```text
Total remaining stones = 30
```

Suppose we make a move and leave a game in which the opponent can optimally obtain:

```text
18 stones
```

Then we must eventually get:

```text
30 - 18
= 12
```

stones.

So:

```text
our_result = total_remaining - opponent_result
```

This automatically includes the stones we take immediately.

We don't need to separately add the stones taken in the current move.

---

# 9. Prefix Sum vs Suffix Sum

We need to quickly calculate how many stones remain from index `i`.

For example:

```text
piles = [2,7,9,4,4]
```

We can create a suffix sum array.

Define:

```text
suffix[i] = piles[i] + piles[i+1] + ... + piles[n-1]
```

For this example:

```text
suffix[0] = 26
suffix[1] = 24
suffix[2] = 17
suffix[3] = 8
suffix[4] = 4
suffix[5] = 0
```

So:

```text
suffix = [26, 24, 17, 8, 4, 0]
```

Now:

```cpp
suffix[i]
```

immediately tells us the total number of stones remaining.

Without suffix sums, repeatedly calculating the sum would make the solution slower.

---

# 10. Base Case

There are two important cases.

## Case 1: No piles remain

If:

```cpp
i == n
```

then there are no stones left.

Therefore:

```cpp
return 0;
```

---

## Case 2: We Can Take Everything

Suppose:

```text
2 * M >= number of remaining piles
```

Then the current player can take all remaining piles.

Therefore there is no reason to explore further.

We simply return:

```cpp
suffix[i]
```

For example:

```text
remaining piles = 4
M = 2
```

Then:

```text
2 * M = 4
```

The current player can take all 4 piles.

So:

```cpp
return suffix[i];
```

This is also an important optimization.

---

# 11. Memoization

There can be many different paths that reach the same state:

```text
(i, M)
```

For example, we might reach:

```text
solve(5, 3)
```

through different sequences of moves.

But once we have calculated:

```text
solve(5, 3)
```

the answer will always be the same.

Therefore, we store the result.

```cpp
dp[i][M]
```

Initially:

```cpp
memset(dp, -1, sizeof(dp));
```

Then:

```cpp
if (dp[i][M] != -1)
    return dp[i][M];
```

This prevents recalculating the same state.

---

# 12. Complete C++ Solution

```cpp
class Solution {
public:
    int n;

    vector<int> suffix;

    int dp[101][101];

    int solve(int i, int M, vector<int>& piles) {

        // No piles remaining
        if (i == n)
            return 0;

        // Current player can take all remaining piles
        if (2 * M >= n - i)
            return suffix[i];

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M; X++) {

            if (i + X > n)
                break;

            // New M after taking X piles
            int nextM = max(M, X);

            // Opponent's maximum number of stones
            int opponent =
                solve(i + X, nextM, piles);

            // Current player gets everything
            // except what the opponent can obtain
            int current =
                suffix[i] - opponent;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {

        n = piles.size();

        // Build suffix sum
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] =
                piles[i] + suffix[i + 1];
        }

        // Initialize DP
        memset(dp, -1, sizeof(dp));

        // Alice starts from index 0 with M = 1
        return solve(0, 1, piles);
    }
};
```

---

# 13. Dry Run

Let's consider:

```text
piles = [2,7,9,4,4]
```

Total:

```text
2 + 7 + 9 + 4 + 4 = 26
```

Alice starts with:

```text
i = 0
M = 1
```

Since:

```text
2*M = 2
```

Alice has two choices.

---

## Choice 1: Alice takes 1 pile

Alice takes:

```text
2
```

New state:

```text
i = 1
M = max(1,1)
  = 1
```

Now Bob plays from:

```text
[7,9,4,4]
```

Bob will choose the move that maximizes his eventual number of stones.

Our DP calculates Bob's optimal result.

Suppose Bob's optimal result is:

```text
16
```

Then Alice's total result from this branch is:

```text
26 - 16
= 10
```

---

## Choice 2: Alice takes 2 piles

Alice takes:

```text
2 + 7 = 9
```

New state:

```text
i = 2
M = max(1,2)
  = 2
```

Now Bob can take up to:

```text
2 * M
= 4
```

remaining piles.

There are only:

```text
[9,4,4]
```

three piles left.

Therefore Bob can take all of them.

Bob gets:

```text
9 + 4 + 4
= 17
```

Alice gets:

```text
26 - 17
= 9
```

So Alice compares:

```text
Choice 1 -> 10
Choice 2 -> 9
```

and chooses:

```text
10
```

Therefore the answer is:

```text
10
```

---

# 14. Why the DP Represents Both Alice and Bob

A common confusion is:

> "Where do we tell the program whether it is Alice's turn or Bob's turn?"

We don't need to.

The function:

```cpp
solve(i, M)
```

always means:

> Maximum stones the **current player** can obtain.

Suppose Alice calls:

```cpp
solve(0, 1)
```

This represents Alice's turn.

After Alice chooses `X`, we call:

```cpp
solve(i + X, max(M, X))
```

Now it is Bob's turn.

Inside that call, Bob is considered the "current player."

Then Bob makes a move, and the next recursive call represents Alice's turn again.

So the same function naturally alternates:

```text
Alice
  ↓
Bob
  ↓
Alice
  ↓
Bob
  ↓
...
```

This is a very common technique in two-player minimax DP.

---

# 15. Why We Don't Store Alice's Score and Bob's Score

We could theoretically create a more complicated DP containing:

```text
Alice's score
Bob's score
whose turn
i
M
```

But this is unnecessary.

Because every stone will eventually belong to either the current player or the opponent:

```text
Total = Current player's stones + Opponent's stones
```

Therefore:

```text
Current player's stones
=
Total - Opponent's stones
```

This lets us use a much simpler state:

```text
(i, M)
```

---

# 16. State Transition Visualization

The entire recurrence can be visualized like this:

```text
                solve(i, M)
                    |
          -----------------------
          |         |           |
        X = 1     X = 2       X = 3 ...
          |         |           |
          v         v           v
 solve(i+1,...) solve(i+2,...) solve(i+3,...)
          |         |           |
          |         |           |
       Opponent  Opponent    Opponent
          |         |           |
          v         v           v
       subtract  subtract     subtract
          |         |           |
          --------- | -----------
                    |
                 maximum
                    |
                    v
              current answer
```

More precisely:

```text
solve(i, M)
    |
    | choose X
    v
opponent_state =
solve(i + X, max(M, X))
    |
    v
my_stones =
suffix[i] - opponent_state
    |
    v
take maximum over all X
```

---

# 17. Complexity

There are two dimensions in our DP:

```text
i
M
```

So there are approximately:

```text
O(n²)
```

states.

For every state, we may try up to:

```text
2*M
```

different values of `X`.

Therefore the straightforward complexity is approximately:

```text
Time Complexity:  O(n³)

Space Complexity: O(n²)
```

For:

```text
n <= 100
```

this is easily manageable.

---

# 18. Important Optimization

This condition:

```cpp
if (2 * M >= n - i)
    return suffix[i];
```

is very important.

Suppose:

```text
n = 100
i = 80
M = 10
```

Remaining piles:

```text
100 - 80 = 20
```

Maximum piles we can take:

```text
2 * M = 20
```

Therefore we can take everything immediately.

Instead of trying:

```text
X = 1
X = 2
X = 3
...
X = 20
```

we simply return:

```cpp
suffix[i]
```

This reduces unnecessary recursive work.

---

# 19. Why This Is Minimax

The problem is essentially a **minimax game**.

The current player wants to maximize their stones.

The opponent also wants to maximize their own stones.

Therefore, from our perspective:

```text
Opponent's best result
```

is something we want to minimize.

Our recurrence captures this indirectly:

```text
our_result
=
total_remaining
-
opponent_best_result
```

Since the opponent's best result is being subtracted, choosing a move that gives the opponent many stones gives us fewer stones.

Then we take the maximum among our possible moves.

So conceptually:

```text
              Our turn
                  |
          Try every move
                  |
                  v
          Opponent's turn
                  |
          Opponent maximizes
                  |
                  v
       Our result = Total - Opponent
                  |
                  v
            We maximize
```

---

# 20. The Most Important Three Lines

If you want to remember the solution for interviews, focus on these three pieces.

### 1. State

```cpp
solve(i, M)
```

means:

> Maximum stones the current player can obtain starting at `i` with `M`.

### 2. Opponent transition

```cpp
solve(i + X, max(M, X))
```

because after taking `X` piles, the opponent starts at `i + X`.

### 3. Score calculation

```cpp
int current = suffix[i] - opponent;
```

because:

```text
Total remaining stones
=
My stones + Opponent's stones
```

Therefore:

```text
My stones
=
Total remaining stones - Opponent's stones
```

---

# 21. Final Template to Remember

For similar two-player DP problems, this pattern is useful:

```cpp
int solve(state) {

    if (game_over)
        return 0;

    if (memo[state] != -1)
        return memo[state];

    int best = 0;

    for (each possible move) {

        int opponent = solve(next_state);

        int current =
            total_remaining - opponent;

        best = max(best, current);
    }

    return memo[state] = best;
}
```

For Stone Game II, the state is:

```text
(i, M)
```

and the move is:

```text
X = 1 ... 2*M
```

with:

```text
next_i = i + X
next_M = max(M, X)
```

That is the core idea behind the entire solution.

