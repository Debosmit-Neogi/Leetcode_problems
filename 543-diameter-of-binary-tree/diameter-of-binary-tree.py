# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def diameterOfBinaryTree(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: int
        """
        self.diameter = 0 # Global varibale to keep track of maximum diameter

        #Function to visit each node recursively and clacualte left and right depth and return max depth from that level
        def depth(root):

            if root == None:
                return 0
            
            left_depth = depth(root.left)
            right_depth = depth(root.right)

            self.diameter = max(self.diameter, left_depth + right_depth)

            return max(left_depth, right_depth) + 1
        
        depth(root)

        return self.diameter