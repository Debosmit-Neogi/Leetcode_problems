class Solution {
public:
    bool isSubsequence(string s, string t) {
        int prev_ind = -1;
        int count = 0;
        for(int i=0;i<s.size(); i++){
            for(int j=0; j<t.size(); j++){
                if(s[i]==t[j] && j>prev_ind){
                    prev_ind = j;
                    count++;
                    break;

                }
                else{
                    continue;
                }
            }

        }
        if(count==s.size()){
            return true;
        }
        else
            return false;
        
    }
};