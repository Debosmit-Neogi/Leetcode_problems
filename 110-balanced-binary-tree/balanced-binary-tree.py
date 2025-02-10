# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def height_bin_tree(self, root):
        if root == None:
            return 0
        
        q = deque([root])
        count = 0
        while q:
            lev = len(q)
            for _ in range(lev):
                node = q.popleft()

                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            count +=1
        return count

    def isBalanced(self, root):
        """
        :type root: Optional[TreeNode]
        :rtype: bool
        """
        if root == None:
            return True
        q = deque([root])
        while q:
            lev = len(q)
            for _ in range(lev):
                node = q.popleft()
                
                left_ht = self.height_bin_tree(node.left)
                
                right_ht = self.height_bin_tree(node.right)

                if abs(left_ht - right_ht) > 1:
                    return False
                
                # Continie BFS
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return True
                

    
    