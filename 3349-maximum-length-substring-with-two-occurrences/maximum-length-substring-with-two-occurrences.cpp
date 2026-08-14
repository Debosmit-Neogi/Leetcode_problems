class Solution {
public:
    bool two_occurance(string s){
        // return true if all chars in a substring have atmost 2 chars

        vector<int>freq(26,0);

        for(char c = 0; c<s.length(); c++){
            freq[s[c] - 'a']++;
        }

        for(int i: freq){
            if(i>2){
                return false;
            }
        }
        return true;
    }

    int maximumLengthSubstring(string s) {
        int max_len = 0;
        

        for(int i = 0; i<s.length(); i++){
            int curr_len = 0;
            for(int j = i; j<s.length(); j++ ){

                if(two_occurance(s.substr(i,j-i+1)) == true){
                    curr_len ++;
                    max_len = max(curr_len, max_len);
                }

                else{
                    break;
                }

            }
        }

        return max_len;
    }
};