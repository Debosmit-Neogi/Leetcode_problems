class Solution {
public:
    string convert(string s, int numRows) {
        // If there is only one row (or the string is shorter than the number of rows),
        // the zigzag is just the original string.

        if(numRows == 1 or numRows > s.size()){
            return s;
        }

        // One string for each row of the zigzag.
        vector<string> rows(numRows);

        int currRow = 0; // current row where char will be places
        int dir = 1; // moving down: 1, moving up: -1


        for(int i = 0; i< s.size(); i++){
            // Place the current character in the current row.

            rows[currRow] += s[i];

            // if we reach bottom row: start moving up

            if(currRow == numRows - 1){
                dir = -1; // move up
            }


            // if we reach top row, start moving down

            else if(currRow == 0){
                dir = 1;
            }

            // move to the next row

            currRow = currRow + dir;

        }


        // concatenate all rows to form the ans

        string ans;

        for(string r: rows){
            ans = ans+r;
        }

        return ans;



    }
};