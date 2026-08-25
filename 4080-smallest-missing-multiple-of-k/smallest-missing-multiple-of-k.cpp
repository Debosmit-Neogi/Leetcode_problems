class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        
        // Store all numbers in a hash set
        // so that we can check whether a number
        // exists in nums in O(1) average time.
        unordered_set<int> st(nums.begin(), nums.end());

        // Start with the smallest positive multiple of k.
        int multiple = k;

        // Keep checking k, 2*k, 3*k, ...
        // until we find a multiple that is not present.
        while (st.count(multiple)) {
            multiple += k;
        }

        // The first missing multiple is the answer.
        return multiple;
    }
};