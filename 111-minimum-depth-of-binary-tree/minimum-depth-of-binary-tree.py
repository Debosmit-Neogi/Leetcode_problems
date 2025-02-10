# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def minDepth(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if root == None:
            return 0
        left_ht = self.minDepth(root.left)
        right_ht = self.minDepth(root.right)

        if (left_ht == 0 and right_ht !=0) or (left_ht != 0 and right_ht ==0):
            return max(left_ht, right_ht) + 1
        else:
            return min(left_ht, right_ht) + 1
        