class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //Since the array is sorted, duplicate elements will always be adjacent. We only need to ensure that each unique element is placed in the correct position.
        
        if (nums.empty()) return 0; // Handle empty input
        
        int slow = 0; // Slow pointer for the position of unique elements
        
        for (int fast = 1; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow]) { 
                // Found a unique element
                slow++; 
                nums[slow] = nums[fast]; // Place it at the next unique position
            }
        }
        
        return slow + 1; // Number of unique elements
    }
};
