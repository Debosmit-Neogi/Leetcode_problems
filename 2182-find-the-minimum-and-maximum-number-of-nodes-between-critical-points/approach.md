# Find the Minimum and Maximum Number of Nodes Between Critical Points

## Problem

A critical point in a linked list is either:

- **Local Maximum:** current node is strictly greater than both its previous and next nodes.
- **Local Minimum:** current node is strictly smaller than both its previous and next nodes.

A node can only be a critical point if it has both a previous and a next node.

Given the head of a linked list, return:

```text
[minDistance, maxDistance]
```

where:

- `minDistance` = minimum distance between any two distinct critical points.
- `maxDistance` = maximum distance between any two distinct critical points.
- If there are fewer than two critical points, return `[-1, -1]`.

---

## Approach

We can solve this using a **single traversal** of the linked list.

### 1. Traverse the linked list

We need three nodes at a time:

```text
previous → current → next
```

This allows us to determine whether `current` is a local maximum or local minimum.

A node is critical if:

```text
(current > previous && current > next)
```

or

```text
(current < previous && current < next)
```

---

### 2. Track critical point positions

Instead of storing all critical points, maintain:

- `first` → index of the first critical point.
- `last` → index of the most recent critical point.
- `minDist` → minimum distance found so far.

Suppose the critical points occur at:

```text
2, 5, 7, 10
```

When we encounter position `5`:

```text
distance = 5 - 2 = 3
```

When we encounter position `7`:

```text
distance = 7 - 5 = 2
```

When we encounter position `10`:

```text
distance = 10 - 7 = 3
```

Therefore:

```text
minDistance = 2
```

We only need to compare **consecutive critical points** to find the minimum distance.

---

### 3. Calculate maximum distance

The maximum distance will always be between the **first and last critical points**.

For:

```text
critical points = [2, 5, 7, 10]
```

the maximum distance is:

```text
10 - 2 = 8
```

So we do not need to store every critical point.

---

## Algorithm

1. Handle lists with fewer than 3 nodes.
2. Set:
   - `first = -1`
   - `last = -1`
   - `minDist = INT_MAX`
3. Traverse the linked list using `previous`, `current`, and `next`.
4. For every `current` node:
   - Check whether it is a local maximum or local minimum.
5. If it is a critical point:
   - If this is the first critical point, store its index in `first`.
   - Otherwise:
     - Calculate `index - last`.
     - Update `minDist`.
   - Update `last = index`.
6. After traversal:
   - If fewer than two critical points were found, return `[-1, -1]`.
   - Otherwise return:
     ```text
     [minDist, last - first]
     ```

---

## C++ Implementation

```cpp
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        // Need at least 3 nodes for a critical point
        if (head == nullptr ||
            head->next == nullptr ||
            head->next->next == nullptr) {
            return ans;
        }

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;

        int first = -1;
        int last = -1;

        int minDist = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check if current node is a local maximum or minimum
            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);

            if (isCritical) {

                // First critical point
                if (first == -1) {
                    first = index;
                }
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, index - last);
                }

                // Current critical point becomes the latest one
                last = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        // Fewer than two critical points
        if (first == -1 || first == last) {
            return ans;
        }

        // Minimum distance between consecutive critical points
        ans[0] = minDist;

        // Maximum distance between first and last critical points
        ans[1] = last - first;

        return ans;
    }
};
```

---

## Dry Run

Consider:

```text
5 → 3 → 1 → 2 → 5 → 1 → 2
```

Using 0-based indexing:

```text
Index:  0  1  2  3  4  5  6
Value:  5  3  1  2  5  1  2
```

### Index 2

```text
previous = 3
current  = 1
next     = 2
```

Since:

```text
1 < 3 && 1 < 2
```

index `2` is a **local minimum**.

```text
first = 2
last  = 2
```

---

### Index 4

```text
previous = 2
current  = 5
next     = 1
```

Since:

```text
5 > 2 && 5 > 1
```

index `4` is a **local maximum**.

Distance from previous critical point:

```text
4 - 2 = 2
```

So:

```text
minDist = 2
last = 4
```

---

### Index 5

```text
previous = 5
current  = 1
next     = 2
```

Since:

```text
1 < 5 && 1 < 2
```

index `5` is a **local minimum**.

Distance:

```text
5 - 4 = 1
```

Update:

```text
minDist = 1
last = 5
```

---

### Final Result

First critical point:

```text
first = 2
```

Last critical point:

```text
last = 5
```

Therefore:

```text
minDistance = 1
maxDistance = 5 - 2 = 3
```

Output:

```text
[1, 3]
```

---

## Why Does the Minimum Only Need Consecutive Critical Points?

Suppose the critical point indices are:

```text
c1 < c2 < c3 < c4
```

The distance between `c1` and `c3` is:

```text
c3 - c1
```

which is always greater than:

```text
c2 - c1
```

Similarly, the distance between any non-consecutive critical points is greater than or equal to the distance between some consecutive pair.

Therefore, checking consecutive critical points is sufficient for finding the minimum.

---

## Why Is the Maximum the First-to-Last Distance?

Because all critical points are ordered by their indices:

```text
first < c2 < c3 < ... < last
```

The largest possible difference is:

```text
last - first
```

So the first and last critical points directly give the maximum distance.

---

## Complexity

Let `n` be the number of nodes in the linked list.

### Time Complexity

```text
O(n)
```

We traverse the linked list exactly once.

### Space Complexity

```text
O(1)
```

We only store a few variables and do not store the critical point positions.

---

## Key Takeaway

The important optimization is that we **do not need to store all critical points**.

We only need:

```text
first critical point
last critical point
previous critical point
minimum distance
```

This gives us an `O(n)` time and `O(1)` space solution.
