class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int left = 0, right = height.size() - 1;

        // Two-pointer approach
        while (left < right) {
            // Calculate the current area
            int current_area = min(height[left], height[right]) * (right - left);

            // Update the max_area if the current area is larger
            max_area = max(max_area, current_area);

            // Move the smaller height pointer inward
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};