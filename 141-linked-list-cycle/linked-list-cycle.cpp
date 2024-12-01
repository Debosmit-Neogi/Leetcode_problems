/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // Initialize two pointers: fast and slow
        ListNode *fast = head;
        ListNode *slow = head;

        // Traverse the list
        while (fast != NULL && fast->next != NULL) {
            // Move fast by two steps
            fast = fast->next->next;
            // Move slow by one step
            slow = slow->next;

            // Check if the two pointers meet
            if (fast == slow) {
                return true; // Cycle detected
            }
        }

        // If we exit the loop, no cycle exists
        return false;
    }
};
