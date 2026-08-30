# 2091. Removing Minimum and Maximum

## Problem

You are given a **0-indexed** array of **distinct** integers `nums`.

The goal is to remove both the **minimum** and **maximum** elements from the array.

A deletion can remove an element from either:

- the **front** of the array
- the **back** of the array

Return the **minimum number of deletions** required to remove both the minimum and maximum elements.

---

## Example

### Input

```text
nums = [2,10,7,5,4,1,8,6]
```

The minimum element is `1` at index `5`.

The maximum element is `10` at index `1`.

### Output

```text
5
```

### Explanation

We can remove:

- `2` elements from the front: `[2, 10]`
- `3` elements from the back: `[6, 8, 1]`

Total:

```text
2 + 3 = 5
```

---

## Approach

Let:

- `minIdx` = index of the minimum element
- `maxIdx` = index of the maximum element
- `left = min(minIdx, maxIdx)`
- `right = max(minIdx, maxIdx)`
- `n` = size of the array

There are only **three possible strategies**.

### 1. Remove both from the front

To remove both elements from the front, we need to delete everything up to index `right`.

```text
deletions = right + 1
```

---

### 2. Remove both from the back

To remove both elements from the back, we need to delete everything from index `left` to the end.

```text
deletions = n - left
```

---

### 3. Remove one from the front and one from the back

We can remove the element at `left` from the front and the element at `right` from the back.

From the front:

```text
left + 1
```

From the back:

```text
n - right
```

Total:

```text
deletions = (left + 1) + (n - right)
```

The answer is the minimum of these three possibilities.

---

## C++ Solution

```cpp
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIdx = 0;
        int maxIdx = 0;

        // Find the indices of minimum and maximum elements
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIdx]) {
                minIdx = i;
            }

            if (nums[i] > nums[maxIdx]) {
                maxIdx = i;
            }
        }

        // left = smaller index
        // right = larger index
        int left = min(minIdx, maxIdx);
        int right = max(minIdx, maxIdx);

        // Option 1: Remove both from the front
        int fromFront = right + 1;

        // Option 2: Remove both from the back
        int fromBack = n - left;

        // Option 3: Remove one from each side
        int fromBothSides = (left + 1) + (n - right);

        return min({fromFront, fromBack, fromBothSides});
    }
};
```

---

## Dry Run

For:

```text
nums = [2,10,7,5,4,1,8,6]
```

We get:

```text
minIdx = 5
maxIdx = 1
```

Therefore:

```text
left = 1
right = 5
n = 8
```

### Option 1: Both from front

```text
right + 1
= 5 + 1
= 6
```

### Option 2: Both from back

```text
n - left
= 8 - 1
= 7
```

### Option 3: One from each side

```text
(left + 1) + (n - right)
= (1 + 1) + (8 - 5)
= 2 + 3
= 5
```

Therefore:

```text
answer = min(6, 7, 5)
       = 5
```

---

## Complexity

### Time Complexity

Finding the minimum and maximum indices requires one traversal:

```text
O(n)
```

### Space Complexity

We only use a few variables:

```text
O(1)
```

---

## Key Insight

We do **not** need to actually perform the deletions.

Once we know the positions of the minimum and maximum elements, there are only three possible optimal strategies:

```text
1. Both from front
2. Both from back
3. One from front + one from back
```

So the problem reduces to calculating the cost of these three strategies and taking the minimum.
