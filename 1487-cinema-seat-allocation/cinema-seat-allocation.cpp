class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

        unordered_map<int, unordered_set<int>> rows;

        // Store reserved seats for each row
        for (auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Seats 1 and 10 don't affect any group
            if (col >= 2 && col <= 9) {
                rows[row].insert(col);
            }
        }

        // Rows with no relevant reservations can fit 2 groups
        int answer = (n - rows.size()) * 2;

        // Process rows that have reservations
        for (auto it = rows.begin(); it != rows.end(); ++it) {

            unordered_set<int>& reserved = it->second;

            bool left = true;
            bool middle = true;
            bool right = true;

            // Seats 2,3,4,5
            for (int seat = 2; seat <= 5; seat++) {
                if (reserved.count(seat)) {
                    left = false;
                    break;
                }
            }

            // Seats 4,5,6,7
            for (int seat = 4; seat <= 7; seat++) {
                if (reserved.count(seat)) {
                    middle = false;
                    break;
                }
            }

            // Seats 6,7,8,9
            for (int seat = 6; seat <= 9; seat++) {
                if (reserved.count(seat)) {
                    right = false;
                    break;
                }
            }

            // Left and right don't overlap,
            // so both groups can be placed.
            if (left && right) {
                answer += 2;
            }
            else if (left || middle || right) {
                answer += 1;
            }
        }

        return answer;
    }
};