# Lexicographically Greater Permutation of `s` Closest to `target`

## Problem

Given a string `s` and a string `target` of the same length (i.e. `target` is
built from some rearrangement of the letters of `s`), find the **smallest
permutation of `s`'s characters that is strictly greater than `target`**
(lexicographically). If no such permutation exists, return an empty string.

This is the classic "next permutation constrained to a target" problem —
similar in spirit to `next_permutation`, but instead of using the letters of
`target` itself, you're free to use *any* arrangement of the letters
available in `s`, and you want the result to just barely beat `target`.

## Approach

The idea mirrors the standard "next greater permutation" technique, adapted
to work with a **frequency count** of available characters instead of a
single fixed array.

### Step 1 — Match `target` greedily from the left

Using a frequency array `freq[26]` built from `s`, walk through `target`
from left to right and "consume" characters as long as they're available:

```cpp
while (i < n && freq[target[i] - 'a'] > 0) {
    freq[target[i] - 'a']--;
    i++;
}
```

- If we consume the **entire** `target` (`i == n`), it means `s`'s letters
  can exactly reproduce `target`. In that case we must backtrack from the
  **last index** (`n - 1`) to find a larger arrangement.
- If we get stuck at some index `i` (`target[i]`'s letter ran out), that's
  the first position where our matched prefix diverges from what's
  achievable — this becomes our starting point for the backtrack search.

### Step 2 — Backtrack from `start` to find a pivot

Scan positions `j` from `start` down to `0`. At each `j`:

1. If `j` was part of the matched prefix (`j < i`), "un-consume" that
   character — put it back into `freq`, since we're now free to reuse it.
2. Look for the **smallest available character strictly greater** than
   `target[j]`.
3. If one is found, that position `j` becomes the **pivot**:
   - Keep everything before `j` identical to `target`.
   - Place the smallest valid character greater than `target[j]` at
     position `j`.
   - Fill the remaining positions with all leftover characters in
     **ascending order** (this guarantees the smallest possible suffix,
     keeping the whole string as close to `target` as possible while still
     being greater).
4. Return this constructed string immediately.

If no such pivot is found after scanning all positions down to `0`, no
permutation of `s` can exceed `target`, so return `""`.

## Code

```cpp
class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Count characters in s
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        // Number of characters matched with target
        int i = 0;
        while (i < n && freq[target[i] - 'a'] > 0) {
            freq[target[i] - 'a']--;
            i++;
        }

        int start = (i == n) ? n - 1 : i;

        // Try positions from right to left
        for (int j = start; j >= 0; j--) {
            if (j < i) {
                freq[target[j] - 'a']++;
            }

            int targetChar = target[j] - 'a';
            for (int c = targetChar + 1; c < 26; c++) {
                if (freq[c] == 0) continue;

                string ans = target.substr(0, j);
                ans += char('a' + c);
                freq[c]--;

                for (int x = 0; x < 26; x++) {
                    ans += string(freq[x], char('a' + x));
                }
                return ans;
            }
        }

        return "";
    }
};
```

## Walkthrough Example

Suppose `s = "aabbcc"` and `target = "abccba"`.

1. `freq = {a:2, b:2, c:2}`
2. Match against `target`:
   - `target[0] = 'a'` → available, consume → `freq = {a:1,b:2,c:2}`, `i=1`
   - `target[1] = 'b'` → available, consume → `freq = {a:1,b:1,c:2}`, `i=2`
   - `target[2] = 'c'` → available, consume → `freq = {a:1,b:1,c:1}`, `i=3`
   - `target[3] = 'c'` → **not available** (0 left) → stop, `i = 3`
3. `start = i = 3`.
4. At `j = 3`: `target[3] = 'c'`. Look for a character `> 'c'` in `freq` —
   none available (`freq` only has a, b, c). Move on.
5. At `j = 2`: restore `target[2] = 'c'` → `freq = {a:1,b:1,c:2}`. Look for
   a character `> 'c'` — none. Move on.
6. At `j = 1`: restore `target[1] = 'b'` → `freq = {a:1,b:2,c:2}`. Look for
   a character `> 'b'` — `'c'` is available!
   - Prefix = `target.substr(0,1) = "a"`
   - Add `'c'` → `"ac"`, `freq = {a:1,b:2,c:1}`
   - Append remaining sorted: `"abbcc"` → wait, sorted from `freq` gives
     `a,b,b,c` → final answer: `"acabbc"`... *(exact remaining order
     depends on final freq counts — always ascending)*

The key guarantee: the returned string is the **smallest string greater
than `target`** achievable using exactly the letters of `s`.

## Complexity

- **Time:** `O(n + 26·n)` ≈ `O(n)` — one pass to match, one pass (worst
  case) to backtrack, and each pivot search scans at most 26 letters plus
  rebuilds an `O(n)` string.
- **Space:** `O(26) + O(n)` for the frequency array and the output string.

## Edge Cases Handled

- **`target` exactly reproducible from `s`:** backtracking starts from the
  last index (`n - 1`), correctly treating it like a "next permutation"
  problem.
- **No greater permutation exists** (e.g. `s`'s letters are already at
  their maximum arrangement, like `"cba"` for target `"cba"`): the loop
  exhausts all positions and returns `""`.
- **Mismatch early in `target`:** if `target[i]` uses a character not
  available at all in `freq`, matching stops immediately at that index,
  and the pivot search begins right there — no unnecessary backtracking
  through already-matched positions.
