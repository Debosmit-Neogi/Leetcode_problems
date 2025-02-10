# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def averageOfLevels(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: List[float]
        """
        ## Apply BFS
        q = deque([root])
        ans = []
        while q:
            level = len(q)
            count = 0
            sum = 0.0
            for _ in range(level):
                node = q.popleft()
                sum += node.val
                count += 1
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ans.append(sum/count)
        return ans