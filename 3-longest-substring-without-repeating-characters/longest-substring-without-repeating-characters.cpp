class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        if(s.size() == 0)
            return 0;
        
        int len = s.size();
        int max_len = 1;
        int curr_len = 1;
        int count[256]; // store all characters in ASCII including a-z and A-Z

        for(int i=0; i<len-1;i++){
            fill(begin(count), end(count), 0); 
            count[s[i]] +=1;
            curr_len = 1;
            for(int j=i+1; j<len; j++){
                count[s[j]] +=1;
                if(count[s[j]] ==1){
                    curr_len +=1;
                    max_len = max(max_len, curr_len);
                }

                else{
                    break;
                }
            }
            
            }

        return max_len;

        }

    };
