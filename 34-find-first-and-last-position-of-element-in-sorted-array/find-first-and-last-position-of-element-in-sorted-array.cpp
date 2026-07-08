class Solution {
public:

    int searchLeft(vector<int>nums, int target){
        int left = 0, right = nums.size()-1;

        int ans = -1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target){
                //don't stop -> search in the left for 1st occurance
                right = mid-1;
                ans = mid;
                
            }

            else if(nums[mid] > target){
                right = mid - 1;
            }

            else if(nums[mid] < target){
                left = mid+1;
            }
        }
        return ans;
    }

    int searchRight(vector<int>nums, int target){
        int left = 0, right = nums.size()-1;

        int ans = -1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target){
                //don't stop -> search in the right for 1st occurance

                left = mid+1;
                ans = mid;
            }

            else if(nums[mid] > target){
                right = mid - 1;
            }

            else if(nums[mid] < target){
                left = mid+1;
            }
        }
        return ans;
    }
    vector<int> searchRange(vector<int>& nums, int target) {

        vector<int>res;

        res.push_back(searchLeft(nums, target));
        res.push_back(searchRight(nums, target));

        return res;
        
    }
};