/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        ListNode* temp=head;
        int i=0;
        int len = 0;

        while(temp!= NULL){
            temp = temp->next;
            len++;
        }

        // edge case: num of elements (len) == n (in that case delete head. so have to return next element as head)
        if(n==len){
            return head->next;
        }

        temp = head;
        while(i< len-n-1){
            temp = temp->next;
            i++;
        }
        
        temp->next = temp->next->next;

        return head;
    }
};