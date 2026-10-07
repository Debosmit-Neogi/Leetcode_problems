class Solution {
public:

    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            }
            else if (c == ')') {
                balance--;

                // More ')' than '('
                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            int size = q.size();

            // Process one BFS level
            while (size--) {
                string curr = q.front();
                q.pop();

                if (isValid(curr)) {
                    result.push_back(curr);
                    found = true;
                }

                // If we already found valid strings at this level,
                // don't generate strings with more removals.
                if (found)
                    continue;

                // Generate strings by removing one character
                for (int i = 0; i < curr.size(); i++) {

                    // Removing letters is unnecessary.
                    if (curr[i] != '(' && curr[i] != ')')
                        continue;

                    string next = curr.substr(0, i) +
                                  curr.substr(i + 1);

                    if (!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }

            // Valid strings found using minimum removals
            if (found)
                break;
        }

        return result;
    }
};