
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // {free_time, weight, index}
        using T = tuple<long long, int, int>;

        priority_queue<T, vector<T>, greater<T>> busy;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for (int j = 0; j < m; j++) {

            time = max(time, (long long)j);

            // Release servers that have completed their tasks.
            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If all servers are busy, jump to the
            // earliest completion time.
            if (available.empty()) {

                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Choose the server with minimum weight and index.
            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;

            // Assign task and update server's availability time.
            busy.push({
                time + tasks[j],
                weight,
                index
            });
        }

        return ans;
    }
};
