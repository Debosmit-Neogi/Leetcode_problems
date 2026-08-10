# 1510. Stone Game IV - Solution Approach

## Problem Statement
Alice and Bob take turns playing a game, with Alice starting first. Initially, there are `n` stones in a pile. On each player's turn, they must remove a **perfect square** number of stones (1, 4, 9, 16, ...). The player who removes the last stone **wins**. Given `n`, return `true` if Alice wins, otherwise `false`.

**Examples:**
- n = 1 → true (Alice removes 1 and wins)
- n = 2 → false (Alice removes 1, Bob removes last)
- n = 4 → true (Alice removes 4 and wins immediately)
- n = 7 → false (Alice cannot force a win)

---

## Solution Approach

### Intuition
This is a **deterministic impartial combinatorial game** with optimal substructure and overlapping subproblems, making it perfect for **Dynamic Programming**.

### Key Observations
1. **State**: Defined solely by remaining stones (`i`)
2. **Winning State**: Exists at least one move leading to opponent's losing state
3. **Losing State**: All moves lead to opponent's winning states
4. **Base Case**: 0 stones = losing (cannot make a move)

### Dynamic Programming Formulation

#### State Definition
- dp[i] = true if current player can force a win with i stones
- dp[i] = false if current player will lose with i stones

#### Transition Formula
- dp[i] = true if ∃ square x² ≤ i such that dp[i - x²] == false
- dp[i] = false otherwise (all moves lead to dp[remaining] == true)


#### Why This Works
For each possible move `(x²)`:
1. Current player removes `x²` stones
2. Remaining: `i - x²` stones for opponent
3. If `dp[i - x²] == false`, opponent loses → current player wins
4. If `dp[i - x²] == true`, opponent wins → that move fails

### Algorithm Steps

1. **Initialize**: Create `dp` array of size `n + 1`, all `false`
2. **Base Case**: `dp[0] = false` (no stones = lose)
3. **Fill DP** (bottom-up):
   - For `i = 1` to `n`:
     - Try every perfect square `x² ≤ i`:
       - If `dp[i - x²] == false`:
         - Set `dp[i] = true` and break
4. **Return**: `dp[n]`

### Complexity Analysis

| Complexity | Value |
|------------|-------|
| **Time** | O(n · √n) |
| **Space** | O(n) |

**Time**: Outer loop runs `n` times, inner loop iterates over perfect squares: √i times → Σᵢ₌₁ⁿ √i = O(n√n)

**Space**: DP array of size `n + 1`

---

## Dry Run Examples

### Example 1: n = 4

Initialize: `dp = [F, F, F, F, F]`

| i | Squares ≤ i | Moves Tested | dp[remaining] | Result | dp[i] |
|---|-------------|--------------|---------------|--------|-------|
| 1 | 1 | remaining=0 | dp[0]=F | Winning | T |
| 2 | 1 | remaining=1 | dp[1]=T | Losing | F |
| 3 | 1 | remaining=2 | dp[2]=F | Winning | T |
| 4 | 1,4 | rem(1)=3: dp[3]=T | rem(4)=0: dp[0]=F | Winning | T |

**Final**: `dp[4] = true` → Alice wins!

### Example 2: n = 7

| i | Squares ≤ i | Moves Tested | dp[remaining] | Result | dp[i] |
|---|-------------|--------------|---------------|--------|-------|
| 1 | 1 | rem=0: F | Winning | T |
| 2 | 1 | rem=1: T | Losing | F |
| 3 | 1 | rem=2: F | Winning | T |
| 4 | 1,4 | rem(1)=3: T | rem(4)=0: F | Winning | T |
| 5 | 1,4 | rem(1)=4: T | rem(4)=1: T | Losing | F |
| 6 | 1,4 | rem(1)=5: F | rem(4)=2: F | Winning | T |
| 7 | 1,4 | rem(1)=6: T | rem(4)=3: T | Losing | F |

**Final**: `dp[7] = false` → Alice loses!

### DP Table Visualization (n = 7)


```text
State:  0  1  2  3  4  5  6  7
dp:     F  T  F  T  T  F  T  F
        ↓  ↓  ↓  ↓  ↓  ↓  ↓  ↓
        L  W  L  W  W  L  W  L
```

**Legend**: W = Winning, L = Losing

### Losing Positions Pattern
0, 2, 5, 7, 10, 12, 15, 17, 20, ...

Differences: 2, 3, 2, 3, 2, 3, ... (periodicity of 5)

---

## Code Implementation

```cpp
class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] = true if current player can force a win with i stones
        vector<bool> dp(n + 1, false);
        
        // dp[0] = false: no stones means current player cannot move
        
        for (int i = 1; i <= n; i++) {
            // Try every perfect square <= i
            for (int x = 1; x * x <= i; x++) {
                int square = x * x;
                int remaining = i - square;
                
                // If opponent is in losing state, this is a winning move
                if (dp[remaining] == false) {
                    dp[i] = true;
                    break; // One winning move is enough
                }
            }
        }
        
        return dp[n];
    }
};
