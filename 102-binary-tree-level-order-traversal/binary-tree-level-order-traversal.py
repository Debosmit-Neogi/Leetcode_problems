# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def levelOrder(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[List[int]]
        """
        if root == None:
            return []
        ans = []
        q = deque([root])

        while q:
            level = len(q)
            lev_node = []
            for _ in range(level):
                node = q.popleft()
                lev_node.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ans.append(lev_node)
            
        return ans

        