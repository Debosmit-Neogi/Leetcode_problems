class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

        // Store reserved seats for each affected row.
        unordered_map<int, int> rows;

        // We only care about seats 2 through 9.
        // Represent seats using bits.
        for (auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                rows[row] |= (1 << col);
            }
        }

        // Initially, every row can fit 2 groups.
        int answer = (n - rows.size()) * 2;

        for (auto& [row, mask] : rows) {

            // Check:
            // seats 2,3,4,5
            bool left =
                !(mask & (1 << 2)) &&
                !(mask & (1 << 3)) &&
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5));

            // Check:
            // seats 6,7,8,9
            bool right =
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7)) &&
                !(mask & (1 << 8)) &&
                !(mask & (1 << 9));

            // Check:
            // seats 4,5,6,7
            bool middle =
                !(mask & (1 << 4)) &&
                !(mask & (1 << 5)) &&
                !(mask & (1 << 6)) &&
                !(mask & (1 << 7));

            if (left && right) {
                // Can fit two groups:
                // [2,3,4,5] and [6,7,8,9]
                answer += 2;
            }
            else if (left || middle || right) {
                // Can fit at least one group.
                answer += 1;
            }
        }

        return answer;
    }
};