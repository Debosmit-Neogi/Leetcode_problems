class Solution(object):
    def minBitFlips(self, start, goal):
        """
        :type start: int
        :type goal: int
        :rtype: int
        """

        xor_res = start^goal
        count=0
        while xor_res:
            count+= xor_res & 1
            xor_res >>= 1
        return count
        