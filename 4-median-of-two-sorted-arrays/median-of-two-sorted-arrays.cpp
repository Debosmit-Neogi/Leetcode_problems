class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        vector<int> merged;

        int i = 0, j = 0;

        // Merge
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i] <= nums2[j]){
                merged.push_back(nums1[i++]);
            }
            else{
                merged.push_back(nums2[j++]);
            }
        }

        // Add remaining
        while(i < nums1.size()){
            merged.push_back(nums1[i]);
            i++;
        }

        while(j < nums2.size()){
            merged.push_back(nums2[j]);
            j++;
        }

        int len = merged.size();

        // Median
        if(len % 2 == 0){
            return (merged[len/2 - 1] + merged[len/2]) / 2.0;
        }
        else{
            return merged[len/2];
        }
    }
};