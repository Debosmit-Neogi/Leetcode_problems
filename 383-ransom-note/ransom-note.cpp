class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if(magazine.size()<ransomNote.size()){
            return false;
        }
        // if(magazine.size() == ransomNote.size() && magazine != ransomNote){
        //     return false;
        // }

        if(magazine == ransomNote){
            return true;
        }
        int count1[26] = {0};
        int count2[26] = {0};

        for(int i=0; i<ransomNote.size(); i++){
            count1[ransomNote[i]-'a']++;
        }

        for(int j=0; j<magazine.size(); j++){
            count2[magazine[j]-'a']++;
        }

        for(int i=0;i<26;i++){
            if(count1[i]> count2[i]){
                return false;
            }
        }
        return true;

        
    }
};