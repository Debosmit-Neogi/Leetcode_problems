class Solution {
public:
    bool isAnagram(string s, string t) {
        long long int freq[26] = {0};
        long long int freq1[26] = {0};

        for(int i=0;i<s.size();i++){
            freq[s[i]-'a']++;
        }
        for(int i=0;i<t.size();i++){
            freq1[t[i]-'a']++;
        }

        for(int i=0;i<26;i++){
            if(freq[i]!=freq1[i])
                return false;
        }

        return true;
        
    }
};