# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def widthOfBinaryTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        if root == None:
            return 0
        q = deque([(root, 0)]) # Store node, position idx
        max_width = 0
        while q:
            levels = len(q)
            _, first_idx = q[0]
            _, last_idx = q[-1]
            max_width = max(max_width, last_idx - first_idx + 1)
            for _ in range(levels):
                node, idx = q.popleft()
                if node.left:
                    q.append((node.left, 2*idx ))
                if node.right:
                    q.append((node.right, 2*idx+1))
        return max_width

