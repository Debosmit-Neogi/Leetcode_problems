class Solution(object):
    def minEatingSpeed(self, piles, h):
        """
        :type piles: List[int]
        :type h: int
        :rtype: int
        """
        def time_taken(rate):
            time = 0
            for i in range(len(piles)):
                if max(piles[i], rate)% rate == 0:
                    time +=  max(piles[i], rate)//rate
                else:
                    time +=  max(piles[i], rate)//rate + 1
            return time

        left = 1
        right = max(piles)

        while(left< right):
            mid = (left + right)//2
            # if time to eat is > h: Increase rate
            if time_taken(mid) > h:
                left = mid + 1
            # if time to eat is <=h: try to search for smaller rate
            else:
                right = mid
        

        return left
        