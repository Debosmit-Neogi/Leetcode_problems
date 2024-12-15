class Solution(object):
    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        rows = len(grid)
        cols = len(grid[0])
        def dfs(r, c):
            if r<0 or c<0 or r>=rows or c>=cols or grid[r][c] == "0":
                return
            
            grid[r][c] = "0"

            #Explore all directions
            dfs(r + 1, c)  # Down
            dfs(r - 1, c)  # Up
            dfs(r, c + 1)  # Right
            dfs(r, c - 1)  # Left
        # Traverse every cell in the grid
        count = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "1":
                    # Found a new island
                    count += 1
                    # Mark all connected land as visited
                    dfs(r, c)

        return count

        