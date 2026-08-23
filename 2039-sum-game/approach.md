# Sum Game

## Problem

Alice and Bob take turns playing a game.

You are given a string `num` of even length containing digits and `'?'`.

On each turn:

1. Choose an index containing `'?'`.
2. Replace `'?'` with any digit from `0` to `9`.

Alice plays first.

When there are no more `'?'` characters:

- Bob wins if the sum of digits in the first half equals the sum in the second half.
- Alice wins if the two sums are different.

Return `true` if Alice wins, otherwise return `false`.

---

## Example

**Input**

```text
num = "?6?6?000?3"
```

**Output**

```text
true
```

**Explanation**

Split the string into two halves:

```text
Left:  ? 6 ? 6 ?
Right: 0 0 0 ? 3
```

Known digit sums:

```text
leftSum = 6 + 6 = 12
rightSum = 0 + 0 + 0 + 3 = 3
```

Therefore:

```text
sumDiff = leftSum - rightSum
        = 12 - 3
        = 9
```

Number of unknown digits:

```text
leftQ = 3
rightQ = 1
```

Therefore:

```text
qDiff = leftQ - rightQ
      = 3 - 1
      = 2
```

The difference in the number of `?` is even.
Bob can force equality only if:

```text
sumDiff = -9 * (qDiff / 2)
```

So:

```text
-9 * (2 / 2) = -9
```

But:

```text
sumDiff = 9
```

Therefore Bob cannot force the two sums to be equal.
So Alice wins:

```text
true
```

---

## Approach

We do not need to simulate every possible move.
Instead, we only need four values:

- `leftSum` → sum of known digits in the first half
- `rightSum` → sum of known digits in the second half
- `leftQ` → number of `?` in the first half
- `rightQ` → number of `?` in the second half

Then calculate:

```text
qDiff = leftQ - rightQ;
sumDiff = leftSum - rightSum;
```

There are three cases.

### Case 1: Same Number of `?`

If:

```text
qDiff == 0
```

both halves have the same number of unknown digits.
Bob can mirror Alice's moves.

For example:

```text
Alice puts 7 on the left.
Bob puts 7 on the right.
```

The added values cancel each other.
Therefore, the result depends only on the known digits.
If the known sums are already different, Alice wins:

```text
if (qDiff == 0)
    return sumDiff != 0;
```

### Case 2: Odd Difference in `?`

If:

```text
abs(qDiff) % 2 == 1
```

the number of `?` differs by an odd amount.
Alice can use the extra move to prevent Bob from making the two sums equal.

Therefore:

```text
if (abs(qDiff) % 2 == 1)
    return true;
```

### Case 3: Even Difference in `?`

Now the difference in the number of `?` is even.
Bob can force equality only if the existing difference between the known sums can be exactly compensated.
Each pair of extra `?` can contribute a difference of `9`.

The required sum difference is:

```text
-9 * (qDiff / 2)
```

Therefore, Bob can force equality only when:

```text
sumDiff == -9 * (qDiff / 2)
```

Since we need to return `true` when Alice wins, we return:

```text
return sumDiff != -9 * (qDiff / 2);
```

### Important

Do not use:

```text
abs(sumDiff) != 9 * abs(qDiff) / 2
```

The sign of `sumDiff` matters.

---

## Algorithm

1. Find the midpoint of the string.
2. Calculate the sum of known digits in the left half.
3. Calculate the sum of known digits in the right half.
4. Count the number of `?` in both halves.
5. Calculate:

   ```text
   qDiff = leftQ - rightQ;
   sumDiff = leftSum - rightSum;
   ```

6. If `qDiff == 0`, return `sumDiff != 0`.
7. If `qDiff` is odd, Alice wins.
8. Otherwise, Bob can win only if:

   ```text
   sumDiff == -9 * (qDiff / 2)
   ```

9. Return the opposite condition because we need to determine whether Alice wins.

---

## Code

### Python

```python
class Solution:
    def sumGame(self, num: str) -> bool:
        n = len(num)
        half = n // 2

        left_sum = 0
        left_q = 0
        for i in range(half):
            if num[i] == '?':
                left_q += 1
            else:
                left_sum += int(num[i])

        right_sum = 0
        right_q = 0
        for i in range(half, n):
            if num[i] == '?':
                right_q += 1
            else:
                right_sum += int(num[i])

        q_diff = left_q - right_q
        sum_diff = left_sum - right_sum

        if q_diff == 0:
            return sum_diff != 0

        if abs(q_diff) % 2 == 1:
            return True

        return sum_diff != -9 * (q_diff // 2)
```

### C++

```cpp
class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        long long leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        for (int i = 0; i < half; i++) {
            if (num[i] == '?') leftQ++;
            else leftSum += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?') rightQ++;
            else rightSum += num[i] - '0';
        }

        int qDiff = leftQ - rightQ;
        long long sumDiff = leftSum - rightSum;

        if (qDiff == 0)
            return sumDiff != 0;

        if (abs(qDiff) % 2 == 1)
            return true;

        return sumDiff != -9LL * (qDiff / 2);
    }
};
```

### Java

```java
class Solution {
    public boolean sumGame(String num) {
        int n = num.length();
        int half = n / 2;

        long leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        for (int i = 0; i < half; i++) {
            char c = num.charAt(i);
            if (c == '?') leftQ++;
            else leftSum += c - '0';
        }

        for (int i = half; i < n; i++) {
            char c = num.charAt(i);
            if (c == '?') rightQ++;
            else rightSum += c - '0';
        }

        int qDiff = leftQ - rightQ;
        long sumDiff = leftSum - rightSum;

        if (qDiff == 0) return sumDiff != 0;
        if (Math.abs(qDiff) % 2 == 1) return true;

        return sumDiff != -9L * (qDiff / 2);
    }
}
```

**Complexity:** O(n) time, O(1) extra space.
