class Solution {
public:
    string smallestPalindrome(string s) {

        sort(s.begin(), s.end());
        int n = s.size();
        vector<char> vec(s.size(), '#');
        int idx = 0;
        for(int i = 0; i<s.size(); ){
            if(s[i] == s[i+1]){
                vec[idx] = s[i];
                vec[n-idx-1] =s[i+1];
                i = i+2; 
                idx++;
            }

            else{
                vec[n/2]=s[i];
                i++;
                // idx++;
            }
        }

        string str(vec.begin(), vec.end());
        return str;
        
    }
};