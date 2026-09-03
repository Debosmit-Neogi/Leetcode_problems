## Approach: Uniform Array (Odd/Even Reachability)

### Problem Idea
We want to know if we can transform every element of `nums1` so that all elements end up with the **same parity** (all odd or all even), using the rule that an even number `x` can be reduced by repeatedly halving it (or similar "reduce toward odd" operations), and comparing against odd numbers already present.

### Key Insight
- If every number is already **even**, we're trivially done (Case 1).
- If every number is already **odd**, we're trivially done (Case 2).
- Otherwise, we have a **mix** of odd and even numbers. The only way to unify everything to **odd** is if for *every* even number `num`, there exists an odd number smaller than it (`minOdd < num`). This is because an even number can only be "matched down" to an odd value that is strictly smaller than it.

### Algorithm
1. **Scan the array once** to find:
   - `hasOdd`: whether any odd number exists.
   - `minOdd`: the smallest odd number found.
2. **Case 1 — No odd numbers**: return `true` (array is already uniform/even).
3. **Case 2 — No even numbers** (`allOdd == true`): return `true` (array is already uniform/odd).
4. **Case 3 — Mixed odd and even**:
   - For every even number `num` in the array, check if `minOdd < num`.
   - If any even number is **≤ minOdd**, it's impossible to unify → return `false`.
   - If all even numbers pass the check → return `true`.

### Complexity
- **Time:** `O(n)` — two linear passes over the array (one to find `minOdd`/`hasOdd`, one to verify evens, plus the `allOdd` check pass).
- **Space:** `O(1)` — only a few scalar variables used.

### Why It Works
The smallest odd number acts as the "anchor" — if even the smallest odd number can't be beaten by an even number, no other (larger) odd number could either. So checking against `minOdd` alone is sufficient to validate all even numbers.
