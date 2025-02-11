# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def invertTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: Optional[TreeNode]
        """
        if root == None:
            return None
        # ans = []
        q = deque([root])

        while q:
            level = len(q)
            for _ in range(level):
                node = q.popleft()
                
                node.left, node.right = node.right, node.left

                if node.left:
                    q.append(node.left)
                
                if node.right:
                    q.append(node.right) 

        return root
