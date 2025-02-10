# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def pathSum(self, root, targetSum):
        """
        :type root: Optional[TreeNode]
        :type targetSum: int
        :rtype: List[List[int]]
        """

        if root == None:
            return []

        res = [] # Stores all valid paths 
        stack = [(root, [root.val], root.val)] # node, path, currSum

        while stack:
            node, path, currSum = stack.pop()

            # base case if: leaf node and currSum == targetsum -> save path in res
            if node.left ==  node.right == None and currSum == targetSum:
                res.append(path)
            
            # DFS on left and right subtree

            if node.left:
                stack.append((node.left, path + [node.left.val], currSum + node.left.val))
            
            if node.right:
                stack.append((node.right, path + [node.right.val], currSum + node.right.val))

        return res