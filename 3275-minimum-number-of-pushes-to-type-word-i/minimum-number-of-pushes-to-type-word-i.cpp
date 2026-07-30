class Solution {
public:
    int minimumPushes(string word) {

        // count and store the frequency of each letter in the string 
        vector<int>freq(26, 0);

        for(int i=0; i<word.size(); i++){
            freq[word[i]-'a']++;
        }

        // sort the array by frequency of letter in descending order
        sort(freq.rbegin(), freq.rend());

        // Greedy Approach (to get minimum number of presses): 
        // The first 8 letters with most frequency should be pressed 1 time (because we have 8 keys 2->9)

        // the next 8 frequent chars will be pressed 2 times

        // the next 8 will be pressed 3 times

        // and the remaining will be pressed 4 times

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