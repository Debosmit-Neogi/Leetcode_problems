class Solution {
public:
    int minimumPushes(string word) {

        vector<int>freq(26, 0);

        for(int i=0; i<word.size(); i++){
            freq[word[i]-'a']++;
        }

        sort(freq.rbegin(), freq.rend());

        int count = 0;

        for(int i=0; i<8; i++){
            count += freq[i]*1;
        }
        
        for(int i=8; i<16; i++){
            count += freq[i]*2;
        }

        for(int i=16; i<24; i++){
            count += freq[i]*3;
        }

        for(int i=24; i<26; i++){
            count += freq[i]*4;
        }

        return count;
    }
};