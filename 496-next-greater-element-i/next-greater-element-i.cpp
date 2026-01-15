class Solution {
public:
    int greater_to_right(vector<int>&nums2, int idx){
        int max_num = nums2[idx];

        for(int i=idx+1; i<nums2.size(); i++){
            if(nums2[i]>max_num){
                max_num = nums2[i];
                break;
            }
            else{
                continue;
            }
        }

        if(max_num == nums2[idx]) return -1;

        return max_num;
    }
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        vector<int> res;
        for(int i=0; i<nums1.size(); i++){
            for(int j=0; j<nums2.size(); j++){

                if(nums1[i]==nums2[j]){
                    res.push_back(greater_to_right(nums2, j));
                }
            }
        }

        return res;
        
    }
};