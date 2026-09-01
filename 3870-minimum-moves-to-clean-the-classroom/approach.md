# Minimum Moves to Collect All Litter — Solution Approach

## Problem Summary

Given a grid `classroom` of size `m x n` containing:
- `S` — the student's starting position
- `L` — a litter cell that must be visited/collected
- `R` — a reset area that fully restores energy upon entry
- `X` — an obstacle (cannot be entered)
- `.` — an empty walkable cell

and a starting `energy` value, find the **minimum number of moves** needed to collect all litter. Each move (up/down/left/right) costs 1 unit of energy, and energy cannot go negative — moving is only allowed if the student has energy remaining. Stepping on an `R` cell resets energy back to the initial `energy` value. Return `-1` if it's impossible to collect all litter.

## Core Idea: BFS over an Augmented State Space

Because moves are unweighted (each move costs exactly 1 step), a plain shortest-path search would work **if** the grid were static. But here the "reachability" of a cell depends on two extra dynamic factors:

1. **How much energy is currently left** — a cell might be reachable now but not later (or vice versa) depending on energy.
2. **Which litter pieces have already been collected** — since we need *all* litter collected, not just the closest one.

So the real state isn't just `(row, col)` — it's:

```
(row, col, energy_remaining, litter_bitmask)
```

Since all edges (moves) have uniform cost 1, **BFS over this expanded state graph** gives the minimum number of moves to reach any target state — in particular, the first state where `litter_bitmask == fullMask`.

## State Encoding

- **Position**: `(r, c)` — grid cell, bounded by `m x n`.
- **Energy**: an integer in `[0, energy]` — capped at the initial energy since `R` resets to the starting value (energy never exceeds the initial cap).
- **Litter mask**: since litter count `k` is small enough for a Leetcode-style constraint, each litter cell is assigned a unique bit index `0..k-1`. The mask is a `k`-bit integer where bit `i` is set once litter `i` has been collected. `fullMask = (1 << k) - 1` represents "all litter collected."

A `visited[r][c][e][mask]` boolean table avoids revisiting identical states, which is essential — without the energy and mask dimensions, BFS could re-expand the same `(r, c)` under different collection/energy circumstances and either loop forever or miss valid shorter paths through a cell.

## Algorithm Steps

1. **Parse the grid**: locate the start `S`, and record every `L` cell's coordinates, assigning each an index for the bitmask.
2. **Edge case**: if there's no litter (`k == 0`), the answer is `0` moves.
3. **Initialize BFS**: push the start state `(sr, sc, energy, mask=0, moves=0)` and mark it visited.
4. **Expand states**: for each dequeued state, try all 4 directions:
   - Skip out-of-bounds or obstacle (`X`) cells.
   - Decrement energy by 1 for the move; skip if this would go negative.
   - If the destination is `R`, reset energy back to the initial `energy`.
   - If the destination is `L`, set the corresponding bit in the litter mask.
   - If this exact `(row, col, energy, mask)` combination hasn't been visited, mark it visited and enqueue it with `moves + 1`.
5. **Termination**: the first time a dequeued state has `mask == fullMask`, its `moves` value is the answer (BFS guarantees this is minimal since all edges have equal weight).
6. If the queue empties without ever reaching `fullMask`, return `-1`.

## Why BFS (Not DFS/Dijkstra) Works Here

- All transitions cost exactly 1 move, so BFS's level-by-level expansion naturally finds the shortest path in terms of move count — no need for Dijkstra's priority queue.
- Expanding the state space to include `(energy, mask)` turns a seemingly stateful/history-dependent problem into a plain shortest-path problem on a larger implicit graph, which is a standard technique for "collect all items" + "resource constraint" grid problems (similar in spirit to the classic Travelling-Salesman-on-grid-with-bitmask pattern, but simplified because BFS suffices instead of needing bitmask DP over pairwise distances).

## Complexity

Let `m, n` be grid dimensions, `E` be the initial energy, and `k` be the number of litter cells.

- **State space size**: `O(m * n * E * 2^k)`
- **Time complexity**: `O(m * n * E * 2^k)` — each state is visited once, and each expansion does O(1) work (4 neighbor checks).
- **Space complexity**: `O(m * n * E * 2^k)` for the `visited` table and the BFS queue.

This is exponential in `k`, so it's only tractable when the number of litter cells is small (typical of constraints where `k ≤ ~15-20`).

## Notes on the Given Implementation

- The `visited` array is sized `energy + 1` to accommodate energy values from `0` to the initial `energy` inclusive.
- The comment block handling `ne == 0` is a no-op / clarifying note — reaching energy `0` on a non-`R` cell is a legitimate (if "stuck unless it's already at the goal") state; it's still pushed and tracked normally, since the mask might already be complete, or a neighboring `R` might be adjacent (handled implicitly, since 0 energy still permits computing `ne = e - 1` on the *next* iteration only if `e > 0` — with `e == 0` all further moves are correctly blocked by the `ne < 0` check).
- Using `queue<State>` (plain BFS) rather than a priority queue is correct and more efficient here specifically because every move has identical cost.

## Correctness Argument

BFS explores states in strictly non-decreasing order of `moves`. The first time any state with `mask == fullMask` is dequeued, no other unexplored path could reach `fullMask` in fewer moves (since BFS guarantees earlier-dequeued states have `moves` ≤ any later-dequeued state's `moves`). Hence, returning `moves` at first reach of `fullMask` is optimal.
