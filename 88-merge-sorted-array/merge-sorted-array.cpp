#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;  // Last valid element in nums1
        int j = 0;      // First element in nums2

        // Compare and swap largest in nums1 with smallest in nums2
        while (i >= 0 && j < n) {
            if (nums1[i] > nums2[j]) {
                swap(nums1[i], nums2[j]);
                i--;
                j++;
            } else {
                // If nums1[i] <= nums2[j], no need for further swaps
                break;
            }
        }

        // Sort both arrays after swapping to maintain order
        sort(nums1.begin(), nums1.begin() + m);  // Sort only the first m elements of nums1
        sort(nums2.begin(), nums2.end());       // Sort nums2

        // Copy nums2 back into nums1
        for (int k = 0; k < n; k++) {
            nums1[m + k] = nums2[k];
        }
    }
};
