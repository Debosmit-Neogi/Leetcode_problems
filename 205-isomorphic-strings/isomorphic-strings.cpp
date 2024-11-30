class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // If lengths are not the same, they can't be isomorphic
        if (s.size() != t.size()) {
            return false;
        }
        
        unordered_map<char, char> map_s_to_t;
        unordered_map<char, char> map_t_to_s;

        for (int i = 0; i < s.size(); ++i) {
            // Check if the current character in s is already mapped to a different character in t
            if (map_s_to_t.find(s[i]) != map_s_to_t.end()) {
                if (map_s_to_t[s[i]] != t[i]) {
                    return false;  // Mapping conflict
                }
            } else {
                map_s_to_t[s[i]] = t[i];
            }

            // Check if the current character in t is already mapped to a different character in s
            if (map_t_to_s.find(t[i]) != map_t_to_s.end()) {
                if (map_t_to_s[t[i]] != s[i]) {
                    return false;  // Reverse mapping conflict
                }
            } else {
                map_t_to_s[t[i]] = s[i];
            }
        }

        return true;
    }
};
