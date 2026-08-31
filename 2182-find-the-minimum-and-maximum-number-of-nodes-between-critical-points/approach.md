Find the Minimum and Maximum Number of Nodes Between Critical Points

Problem

A critical point in a linked list is either:

Local Maximum: current node is strictly greater than both its previous and next nodes.

Local Minimum: current node is strictly smaller than both its previous and next nodes.

A node can only be a critical point if it has both a previous and a next node.

Given the head of a linked list, return:

[minDistance, maxDistance]

where:

minDistance = minimum distance between any two distinct critical points.

maxDistance = maximum distance between any two distinct critical points.

If there are fewer than two critical points, return [-1, -1].

Approach

We can solve this using a single traversal of the linked list.

1. Traverse the linked list

We need three nodes at a time:

previous → current → next

This allows us to determine whether current is a local maximum or local minimum.

A node is critical if:

(current > previous && current > next)

or

(current < previous && current < next)

2. Track critical point positions

Instead of storing all critical points, maintain:

first → index of the first critical point.

last → index of the most recent critical point.

minDist → minimum distance found so far.

Suppose the critical points occur at:

2, 5, 7, 10

When we encounter position 5:

distance = 5 - 2 = 3

When we encounter position 7:

distance = 7 - 5 = 2

When we encounter position 10:

distance = 10 - 7 = 3

Therefore:

minDistance = 2

We only need to compare consecutive critical points to find the minimum distance.

3. Calculate maximum distance

The maximum distance will always be between the first and last critical points.

For:

critical points = [2, 5, 7, 10]

the maximum distance is:

10 - 2 = 8

So we do not need to store every critical point.

Algorithm

Handle lists with fewer than 3 nodes.

Set:

first = -1

last = -1

minDist = INT_MAX

Traverse the linked list using previous, current, and next.

For every current node:

Check whether it is a local maximum or local minimum.

If it is a critical point:

If this is the first critical point, store its index in first.

Otherwise:

Calculate index - last.

Update minDist.

Update last = index.

After traversal:

If fewer than two critical points were found, return [-1, -1].

Otherwise return:

[minDist, last - first]

C++ Implementation

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

Dry Run

Consider:

5 → 3 → 1 → 2 → 5 → 1 → 2

Using 0-based indexing:

Index:  0  1  2  3  4  5  6
Value:  5  3  1  2  5  1  2

Index 2

previous = 3
current  = 1
next     = 2

Since:

1 < 3 && 1 < 2

index 2 is a local minimum.

first = 2
last  = 2

Index 4

previous = 2
current  = 5
next     = 1

Since:

5 > 2 && 5 > 1

index 4 is a local maximum.

Distance from previous critical point:

4 - 2 = 2

So:

minDist = 2
last = 4

Index 5

previous = 5
current  = 1
next     = 2

Since:

1 < 5 && 1 < 2

index 5 is a local minimum.

Distance:

5 - 4 = 1

Update:

minDist = 1
last = 5

Final Result

First critical point:

first = 2

Last critical point:

last = 5

Therefore:

minDistance = 1
maxDistance = 5 - 2 = 3

Output:

[1, 3]

Why Does the Minimum Only Need Consecutive Critical Points?

Suppose the critical point indices are:

c1 < c2 < c3 < c4

The distance between c1 and c3 is:

c3 - c1

which is always greater than:

c2 - c1

Similarly, the distance between any non-consecutive critical points is greater than or equal to the distance between some consecutive pair.

Therefore, checking consecutive critical points is sufficient for finding the minimum.

Why Is the Maximum the First-to-Last Distance?

Because all critical points are ordered by their indices:

first < c2 < c3 < ... < last

The largest possible difference is:

last - first

So the first and last critical points directly give the maximum distance.

Complexity

Let n be the number of nodes in the linked list.

Time Complexity

O(n)

We traverse the linked list exactly once.

Space Complexity

O(1)

We only store a few variables and do not store the critical point positions.

Key Takeaway

The important optimization is that we do not need to store all critical points.

We only need:

first critical point
last critical point
previous critical point
minimum distance

This gives us an O(n) time and O(1) space solution.
