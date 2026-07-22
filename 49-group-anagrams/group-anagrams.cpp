// class Solution {
// public:
//     bool equal_vector(vector<int> a, vector<int>b){
//         int n = a.size();
        
//         for(int i=0; i<n; i++){
//             if((a[i]-b[i])!=0){
//                 return false;
//             }
//             else
//                 continue;
//         }
//         return true;
//     }

//     vector<int> freq_vec(string str){
//         vector<int> ans(26,0);
        
//         for(int i=0; i<str.size(); i++){
//             ans[str[i]-'a']++;
//         }
        
//         return ans;
//     }
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//     vector<vector<string>> ans;
    
//     vector<int> idx_ana; // keep track of the index that is already pushed to temp vector (i.e anagram found)
    
//     for(int i=0; i<strs.size(); i++){
//         vector<string>temp;
//         // if the current string is not identified as anagram yet do processing
//         if(find(idx_ana.begin(), idx_ana.end(), i) == idx_ana.end()){
//         temp.push_back(strs[i]);
//         idx_ana.push_back(i);
        
        
        
//         for(int j=i+1; j<strs.size(); j++){
//             if(equal_vector(freq_vec(strs[i]), freq_vec(strs[j])) && find(idx_ana.begin(), idx_ana.end(), j) == idx_ana.end()){
//                 temp.push_back(strs[j]);
//                 idx_ana.push_back(j);
//             }
             
            
//         }
//         ans.push_back(temp);
//         }
        
       
//     }
    
    
//     return ans;
    
        
// }
// };

class Solution {
public:
    bool equal_vector(vector<int>& a, vector<int>& b) {
        for(int i = 0; i < 26; i++) {
            if(a[i] != b[i]) return false;
        }
        return true;
    }

    vector<int> freq_vec(string& str) {
        vector<int> ans(26, 0);
        for(char c : str) {
            ans[c - 'a']++;
        }
        return ans;
    }
    
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        vector<bool> visited(strs.size(), false);  // O(1) lookup instead of O(n)
        
        // Pre-compute frequency vectors
        vector<vector<int>> freq_cache;
        freq_cache.reserve(strs.size());
        for(string& s : strs) {
            freq_cache.push_back(freq_vec(s));
        }
        
        for(int i = 0; i < strs.size(); i++) {
            if(visited[i]) continue;
            
            vector<string> temp;
            temp.push_back(strs[i]);
            visited[i] = true;
            
            for(int j = i + 1; j < strs.size(); j++) {
                if(!visited[j] && equal_vector(freq_cache[i], freq_cache[j])) {
                    temp.push_back(strs[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(temp);
        }
        
        return ans;
    }
};