# 2904. Shortest and Lexicographically Smallest Beautiful String

## Problem

You are given a binary string `s` and a positive integer `k`.

A substring is **beautiful** if it contains exactly `k` ones.

Return the **shortest** beautiful substring. If multiple beautiful substrings have the same shortest length, return the **lexicographically smallest** one.

If no beautiful substring exists, return an empty string.

---

## Approach

We can solve this using a **sliding window**.

We maintain a window `[left, right]` and keep track of how many `1`s it contains.

### Steps

1. Move `right` from left to right through the string.
2. Whenever `s[right] == '1'`, increment the number of ones.
3. If the window contains more than `k` ones, move `left` forward until it contains at most `k` ones.
4. When the window contains exactly `k` ones:
   - Remove all unnecessary leading `0`s.
   - Now the window is the shortest substring ending at `right` that contains these `k` ones.
5. Compare this substring with the best answer found so far:
   - Prefer a shorter substring.
   - If lengths are equal, prefer the lexicographically smaller substring.

### Why can we remove leading zeroes?

Suppose our window is:

```text
000110
```

and `k = 2`.

The leading zeroes do not contribute any `1`s, so:

```text
110
```

still contains exactly two `1`s and is shorter.

Therefore, whenever the window contains exactly `k` ones, we move `left` past unnecessary leading zeroes.

---

## C++ Solution

```cpp
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        int left = 0;
        int ones = 0;

        // Length of the best substring found so far
        int bestLen = INT_MAX;

        // Best answer
        string answer = "";

        for (int right = 0; right < n; right++) {

            // Add the current character to the window
            if (s[right] == '1') {
                ones++;
            }

            // If there are more than k ones,
            // shrink the window from the left.
            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }

                left++;
            }

            // We now have exactly k ones
            if (ones == k) {

                // Remove unnecessary leading zeroes.
                // They do not affect the number of ones.
                while (s[left] == '0') {
                    left++;
                }

                // Current window is now a candidate answer
                int len = right - left + 1;

                string current = s.substr(left, len);

                // Prefer:
                // 1. Smaller length
                // 2. Lexicographically smaller string
                if (len < bestLen ||
                    (len == bestLen && current < answer)) {

                    bestLen = len;
                    answer = current;
                }
            }
        }

        return answer;
    }
};
```

---

## Example

### Input

```text
s = "100011001"
k = 2
```

We need a substring containing exactly two `1`s.

Some possible substrings are:

```text
"100011"
"11001"
```

`"11001"` has length `5`, while `"100011"` has length `6`.

Therefore, the shortest beautiful substring is:

```text
"11001"
```

### Output

```text
"11001"
```

---

## Complexity

### Time Complexity

```text
O(n)
```

Both `left` and `right` only move forward through the string.

Although we create substrings for candidates, the overall sliding-window traversal is linear.

### Space Complexity

```text
O(n)
```

The returned/candidate strings can require `O(n)` space.

---

## Key Idea

The important observation is:

> For every window containing exactly `k` ones, remove all leading zeroes. This gives the shortest possible substring ending at the current position.

Then we simply keep the shortest candidate, and among candidates with the same length, keep the lexicographically smallest one.
