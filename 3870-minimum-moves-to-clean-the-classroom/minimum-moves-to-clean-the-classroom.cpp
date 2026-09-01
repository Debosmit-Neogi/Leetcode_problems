#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        // Find start and assign an index to every litter cell.
        int sr = -1, sc = -1;
        vector<pair<int, int>> litter;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                } 
                else if (classroom[r][c] == 'L') {
                    litter.push_back({r, c});
                }
            }
        }

        int k = litter.size();

        // No litter to collect.
        if (k == 0)
            return 0;

        // Map litter position -> bit index.
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            auto [r, c] = litter[i];
            litterId[r][c] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            visited[r][c][energy][mask]

            Since energy ranges from 0...energy,
            and mask ranges from 0...(2^k - 1).
        */
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << k, false)
                )
            )
        );

        struct State {
            int r, c;
            int energy;
            int mask;
            int moves;
        };

        queue<State> q;

        visited[sr][sc][energy][0] = true;
        q.push({sr, sc, energy, 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            int r = cur.r;
            int c = cur.c;
            int e = cur.energy;
            int mask = cur.mask;
            int moves = cur.moves;

            if (mask == fullMask)
                return moves;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Outside grid.
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                // Cannot enter obstacles.
                if (classroom[nr][nc] == 'X')
                    continue;

                // Every move costs 1 energy.
                int ne = e - 1;

                // Cannot move if we don't have energy.
                if (ne < 0)
                    continue;

                // Reset area restores energy.
                if (classroom[nr][nc] == 'R') {
                    ne = energy;
                }

                // Collect litter.
                int nmask = mask;

                if (classroom[nr][nc] == 'L') {
                    int id = litterId[nr][nc];
                    nmask |= (1 << id);
                }

                /*
                    If energy becomes 0, we can only continue
                    from an R cell.

                    Since R immediately resets energy above,
                    ne will never remain 0 after entering R.
                */
                if (ne == 0 && classroom[nr][nc] != 'R') {
                    // We can arrive here, but cannot make
                    // another move until reaching a reset.
                    // This state is still valid.
                }

                if (!visited[nr][nc][ne][nmask]) {
                    visited[nr][nc][ne][nmask] = true;

                    q.push({
                        nr,
                        nc,
                        ne,
                        nmask,
                        moves + 1
                    });
                }
            }
        }

        return -1;
    }
};