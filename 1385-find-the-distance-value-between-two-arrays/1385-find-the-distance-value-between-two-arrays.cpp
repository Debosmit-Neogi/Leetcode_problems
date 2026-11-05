class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count = 0;
        
        for (int x : arr1) {
            // Find first element >= x
            auto it = lower_bound(arr2.begin(), arr2.end(), x);
            
            bool ok = true;
            
            // Check the element at or after x
            if (it != arr2.end() && abs(*it - x) <= d) {
                ok = false;
            }
            
            // Check the element just before x
            if (it != arr2.begin()) {
                auto prev = it - 1;
                if (abs(*prev - x) <= d) {
                    ok = false;
                }
            }
            
            if (ok) count++;
        }
        
        return count;
    }
};