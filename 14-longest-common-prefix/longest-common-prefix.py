class Solution(object):
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        prefix = strs[0]
        # Compare the prefix with each string in the list
        for string in strs[1:]:
            # Adjust the prefix length until it matches the start of the string
            while not string.startswith(prefix):
                prefix = prefix[:-1]
                if not prefix:
                    return ""
        
        return prefix


"""

string.startswith(prefix):

Checks whether the current string starts with the prefix.
If it does, the loop ends, and prefix remains unchanged.
If it does not, the loop continues to shorten prefix until it matches the start of the string or becomes empty.
prefix = prefix[:-1]:

This removes the last character from prefix.
For example:
If prefix = "flower" and string = "flow", it becomes prefix = "flowe", then prefix = "flow", which matches string.startswith(prefix).
if not prefix:

Checks if the prefix has been reduced to an empty string (i.e., "").
If it has, it means there is no common prefix, so the function immediately returns "".
Why is this necessary?
The while loop is designed to make the prefix progressively shorter until it satisfies the condition string.startswith(prefix) for the current string.
This ensures that prefix is always the longest common prefix among the strings checked so far.

"""
