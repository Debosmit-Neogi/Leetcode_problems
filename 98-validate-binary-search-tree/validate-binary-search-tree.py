class Solution(object):
    def isValidBST(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        if not root:
            return True

        stack = [(root, float('-inf'), float('inf'))]  # (node, lower_bound, upper_bound)

        while stack:
            node, lower, upper = stack.pop()

            if node.val <= lower or node.val >= upper:
                return False

            if node.right:
                stack.append((node.right, node.val, upper))
            if node.left:
                stack.append((node.left, lower, node.val))

        return True
