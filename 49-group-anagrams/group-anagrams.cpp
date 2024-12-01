class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;

        for (const string& str : strs) {
            string sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end()); // Sort each string to create a key
            anagramMap[sortedStr].push_back(str);    // Group strings by sorted key
        }

        vector<vector<string>> result;
        for (const auto& pair : anagramMap) {
            result.push_back(pair.second);
        }

        return result;
    }
};
