
class Solution {
public:
    vector<int> answer;
    vector<vector<int>> adj, finalTree;
    vector<int> newParent;
    vector<int> last = vector<int>(26, -1);

    void dfs(int u, vector<int>& parent, string& s) {
        int c = s[u] - 'a';

        // Save previous closest ancestor
        int prev = last[c];

        // Determine new parent using original tree
        if (u != 0 && last[c] != -1) {
            newParent[u] = last[c];
        } else {
            newParent[u] = parent[u];
        }

        // Update closest ancestor
        last[c] = u;

        // Traverse original children
        for (int v : adj[u]) {
            dfs(v, parent, s);
        }

        // Backtrack
        last[c] = prev;
    }

    int calculateSize(int u) {
        int sz = 1;

        for (int v : finalTree[u]) {
            sz += calculateSize(v);
        }

        answer[u] = sz;
        return sz;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.resize(n);
        finalTree.resize(n);
        answer.resize(n);
        newParent.resize(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Determine all new parents
        dfs(0, parent, s);

        // Build final tree
        for (int i = 1; i < n; i++) {
            finalTree[newParent[i]].push_back(i);
        }

        // Calculate final subtree sizes
        calculateSize(0);

        return answer;
    }
};
