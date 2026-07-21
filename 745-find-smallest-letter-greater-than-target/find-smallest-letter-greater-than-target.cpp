class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {

        vector<int>arr(letters.size());

        for(int i=0; i<arr.size(); i++){
            arr[i] = letters[i] - target;
        }

        int min_diff = INT_MAX;
        int curr_diff;
        for(int i=0; i<arr.size(); i++){

            if(arr[i]> 0){

                curr_diff = arr[i];
                min_diff = min(curr_diff, min_diff);

            }

            else{
                continue;
            }
        }

        if(min_diff == INT_MAX){
            return letters[0];
        }

        char ans = target + min_diff;
        return ans;

        
        
    }
};