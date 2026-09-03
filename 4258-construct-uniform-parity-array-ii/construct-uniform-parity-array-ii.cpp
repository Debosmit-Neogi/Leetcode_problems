class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        bool hasOdd = false;
        
        // Find the minimum odd number
        for (int num : nums1) {
            if (num % 2 == 1) {
                hasOdd = true;
                minOdd = min(minOdd, num);
            }
        }
        
        // Case 1: All numbers are even → keep as even
        if (!hasOdd) return true;
        
        // Case 2: All numbers are odd → keep as odd  
        bool allOdd = true;
        for (int num : nums1) {
            if (num % 2 == 0) {
                allOdd = false;
                break;
            }
        }
        if (allOdd) return true;
        
        // Case 3: Try to make all odd
        // Every even number must have a smaller odd number
        for (int num : nums1) {
            if (num % 2 == 0) {
                // Check if there exists an odd number smaller than this even number
                if (minOdd >= num) {
                    return false;
                }
            }
        }
        
        // Case 4: Try to make all even
        // The smallest odd number cannot become even (no smaller odd to subtract)
        // So all even is impossible if there's any odd number
        // (We already handled the all even case above when hasOdd is false)
        
        return true;
    }
};