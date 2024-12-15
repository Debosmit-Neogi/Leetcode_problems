class Solution(object):
    def spiralOrder(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        res = []
        # Define boundary conditions
        top = 0
        bottom = len(matrix)-1
        left = 0
        right = len(matrix[0])-1

        while(top<=bottom and left<=right):

            #condition 1: move from l->r along top and then top++
            for col in range(left, right+1):
                res.append(matrix[top][col])
            top = top + 1

            # Condition 2: move from top->bott along right and right--
            for row in range(top, bottom+1):
                res.append(matrix[row][right])
            right = right - 1

            #Condition 3: move from r->l along bottom and bottom--
            if top <= bottom:
                for col in range(right, left-1, -1):
                    res.append(matrix[bottom][col])
                bottom = bottom - 1

            #Condiiton 4: move from bottom->top along left and left++
            if left<=right:
                for row in range(bottom, top-1, -1):
                    res.append(matrix[row][left])
                left = left + 1

        return res

        