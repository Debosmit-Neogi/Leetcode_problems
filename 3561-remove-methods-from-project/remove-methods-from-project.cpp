class Solution {
public:
    // DFS to mark all methods that are suspicious
    void dfs(int node, vector<vector<int>>& adj, vector<int>& suspicious) {

        // Mark the current method as suspicious
        suspicious[node] = 1;

        // Visit all methods invoked by the current method
        for (int next : adj[node]) {

            // If not already visited, continue DFS
            if (!suspicious[next]) {
                dfs(next, adj, suspicious);
            }
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        // Adjacency list representing the invocation graph
        vector<vector<int>> adj(n);

        // Build the graph
        // u -> v means method u invokes method v
        for (auto &edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
        }

        // suspicious[i] = 1 if method i is suspicious
        vector<int> suspicious(n, 0);

        // Step 1:
        // Start DFS from the buggy method k to find all suspicious methods
        dfs(k, adj, suspicious);

        // Step 2:
        // Check whether any non-suspicious method invokes
        // a suspicious method.
        // If such an edge exists, the suspicious group
        // cannot be removed.
        for (auto &edge : invocations) {

            int u = edge[0];
            int v = edge[1];

            // Outside -> Suspicious
            if (!suspicious[u] && suspicious[v]) {

                // Return all methods since nothing can be removed
                vector<int> ans;

                for (int i = 0; i < n; i++) {
                    ans.push_back(i);
                }

                return ans;
            }
        }

        // Step 3:
        // Removal is possible.
        // Return only the non-suspicious methods.
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};