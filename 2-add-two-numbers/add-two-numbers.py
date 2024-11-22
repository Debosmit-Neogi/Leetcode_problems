# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: Optional[ListNode]
        :type l2: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        l3 = ListNode(0)
        h3 = l3
        carry = 0
        
        while l1 or l2 or carry:  # Include carry to handle final carry
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            res = val1 + val2 + carry
            carry = res // 10  # Carry for the next iteration
            res = res % 10      # The value to store in the current node
            
            h3.next = ListNode(res)  # Create the next node with the result
            h3 = h3.next  # Move to the next node
            
            if l1:
                l1 = l1.next  # Move to the next node in l1
            if l2:
                l2 = l2.next  # Move to the next node in l2

        # Now l3: [0,7,0,8]. To remove extra 0, start from l3.next
        return l3.next  # Return the next node to skip the dummy head
