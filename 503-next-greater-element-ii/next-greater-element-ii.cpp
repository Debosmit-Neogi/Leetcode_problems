class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);  // default is -1

        // Pick each element one by one
        for (int i = 0; i < n; i++) {

            // Start checking from the next position
            int currentIndex = (i + 1) % n;

            // We can move at most n-1 steps (full circle except itself)
            int stepsTaken = 0;

            while (stepsTaken < n - 1) {

                // If we find a greater element, store and stop
                if (nums[currentIndex] > nums[i]) {
                    result[i] = nums[currentIndex];
                    break;
                }

                // Move to next index (circularly)
                currentIndex = (currentIndex + 1) % n;
                stepsTaken++;
            }
        }

        return result;
    }
};
