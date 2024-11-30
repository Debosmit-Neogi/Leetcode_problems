class Solution(object):
    def setZeroes(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: None Do not return anything, modify matrix in-place instead.
        """
        m,n = len(matrix), len(matrix[0])
        coords = []
        for i in range(0, m):
            for j in range(n):
                if matrix[i][j] == 0:
                    coords.append((i,j))
        
        for x,y in coords:
            for col in range(n):
                matrix[x][col] = 0
            for row in range(m):
                matrix[row][y] = 0
        # return matrix
                    
        