
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;

        // {completion time, server ID}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > busy;

        vector<int> count(k, 0);

        // Initially all servers are available
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {
            int currTime = arrival[i];

            // Release servers that have completed their requests
            while (!busy.empty() && busy.top().first <= currTime) {
                int server = busy.top().second;
                busy.pop();

                available.insert(server);
            }

            // All servers are busy
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find next available server
            auto it = available.lower_bound(preferred);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            count[server]++;

            available.erase(it);

            // Store completion time
            busy.push({currTime + load[i], server});
        }

        // Find maximum number of handled requests
        int maxRequests = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxRequests) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
