class Solution {
public:
    int findSmallestMissing(vector<int>& nums, int k) {
        unordered_set<int> present(nums.begin(), nums.end());

        int x = k;

        while (present.count(x)) {
            x++;
        }

        return x;
    }

    int missingInteger(vector<int>& nums) {
        vector<int> temp;
        vector<int> prefix_arr;

        int max_length = 0;

        // Prefix must start from index 0
        int i = 0;

        int length = 1;
        temp.clear();
        temp.push_back(nums[i]);

        for(int j = i + 1; j < nums.size(); ) {

            if(nums[j] == nums[j - 1] + 1) {
                temp.push_back(nums[j]);
                length++;
                j++;
            }
            else {
                break;
            }
        }

        if(length > max_length) {
            prefix_arr = temp;
            max_length = length;
        }

        int prefix_sum = 0;

        for(int x : prefix_arr) {
            prefix_sum += x;
        }

        int ans = findSmallestMissing(nums, prefix_sum);

        return ans;
    }
};