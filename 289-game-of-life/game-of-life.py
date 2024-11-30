class Solution(object):
    def gameOfLife(self, board):
        """
        :type board: List[List[int]]
        :rtype: None Do not return anything, modify board in-place instead.
        """
        m, n = len(board), len(board[0])

        # Helper function to count live neighbors
        def count_live_neighbors(row, col):
            directions = [
                (-1, -1), (-1, 0), (-1, 1),
                (0, -1),         (0, 1),
                (1, -1), (1, 0), (1, 1)
            ]
            count = 0
            for dr, dc in directions:
                r, c = row + dr, col + dc
                if 0 <= r < m and 0 <= c < n and abs(board[r][c]) == 1:
                    count += 1
            return count

        # First pass: Update states using encoding
        for i in range(m):
            for j in range(n):
                live_neighbors = count_live_neighbors(i, j)

                # Rule 1 and Rule 3
                if board[i][j] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    board[i][j] = -1  # Alive to dead

                # Rule 4
                if board[i][j] == 0 and live_neighbors == 3:
                    board[i][j] = 2  # Dead to alive

        # Second pass: Finalize the board
        for i in range(m):
            for j in range(n):
                if board[i][j] == -1:
                    board[i][j] = 0
                elif board[i][j] == 2:
                    board[i][j] = 1
        