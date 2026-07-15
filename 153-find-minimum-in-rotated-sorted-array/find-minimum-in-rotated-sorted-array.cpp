class Solution {
public:
    int findMin(vector<int>& nums) {

        // Our main goal is to reach state where: left < right

        int n = nums.size();
        int left =0;
        int right = n-1;
        int curr_ans = nums[0];
        int min_ans = INT_MAX;

        while(left <= right){

            int mid = left + (right-left)/2;

            // this means we have asc sorted array from left -> mid. so we have to search for more minimum from mid -> right. 
            // for now potential minimum is nums[left]

            if(nums[left]<=nums[mid]){
            curr_ans = nums[left];
            min_ans = min(curr_ans, min_ans);

            left = mid+1;
            }

            // this means we don't have asc sorted array from left -> mid. we have asc sorted from mid - > right 
            // so we have to search for more minimum from mid -> left. 
            // for now potential minimum is nums[mid]

            else if(nums[left]>nums[mid]){
            curr_ans = nums[mid];
            min_ans = min(curr_ans, min_ans);

            right = mid-1;
            }



        }
        return min_ans;
        
    }
};