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
