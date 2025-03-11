class Solution(object):
    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
    
        # base cases

        if (n==0):
            return 1
        if(n==1):
            return 1
        
        prev1, prev2 = 1,1
        for i in range(2, n+1):
            curr = prev1 + prev2
            prev2 = prev1
            prev1 = curr
        return prev1