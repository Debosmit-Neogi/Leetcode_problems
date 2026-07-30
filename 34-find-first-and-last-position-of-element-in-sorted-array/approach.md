# Solution Approach: First and Last Position in Sorted Array

## High-Level Strategy

The core idea is to leverage **Binary Search** twice—once to find the leftmost occurrence and once to find the rightmost occurrence of the target.

### Why Binary Search?
Since the array is sorted, binary search gives us O(log n) time complexity, which is optimal for this problem.

---

## The Two-Phase Approach

### Phase 1: Find Leftmost (First Occurrence)
- Perform standard binary search
- When `target` is found, **do not stop**
- Continue searching in the **left half** to check for earlier occurrences
- Keep updating the answer whenever a match is found
- The final stored answer will be the first occurrence

### Phase 2: Find Rightmost (Last Occurrence)
- Perform standard binary search
- When `target` is found, **do not stop**
- Continue searching in the **right half** to check for later occurrences
- Keep updating the answer whenever a match is found
- The final stored answer will be the last occurrence

---

## Key Insight
The only difference between the two searches is the direction we move after finding the target:
- **Left search:** Move `right` pointer leftward (`right = mid - 1`)
- **Right search:** Move `left` pointer rightward (`left = mid + 1`)

By modifying this single step, we can efficiently locate both boundaries without scanning the entire array.

---

## Why This Works
1. **Maintains binary search property** - we still halve the search space each iteration
2. **Preserves sorted order** - we never violate the sorted invariant
3. **Stores candidate answers** - we track the last valid position found
4. **Handles duplicates gracefully** - by continuing search, we naturally find boundaries

---

## Complexity
- **Time:** O(log n) - Two binary searches
- **Space:** O(1) - Only pointer variables used

---

## Edge Cases Handled
| Scenario | Behavior |
|----------|----------|
| Target not in array | Both searches return -1 |
| Single occurrence | Both searches return same index |
| All elements same | Searches find first and last positions |
| Empty array | Returns [-1, -1] |
| Target at boundaries | Search still works correctly |

---

## Alternative Perspective
This problem is equivalent to finding:
- **First occurrence** = `lower_bound` (first element ≥ target)
- **Last occurrence** = `upper_bound` (first element > target) - 1

Our custom binary searches essentially implement these two standard library functions manually.

---

## Summary
The solution transforms a simple binary search into two specialized searches that:
1. Find the left boundary by favoring the left half on matches
2. Find the right boundary by favoring the right half on matches

This elegant modification of the classic binary search algorithm efficiently solves the problem in logarithmic time.
