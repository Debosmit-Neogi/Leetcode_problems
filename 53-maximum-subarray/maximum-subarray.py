class Solution(object):
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        maxSub = nums[0] # 1st element
        curSum = 0

        for i in range(len(nums)):
            if curSum < 0:
                curSum = 0
            
            curSum += nums[i]
            maxSub = max(maxSub, curSum)
        return maxSub
        