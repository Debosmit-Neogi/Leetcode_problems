
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum == 0 || sum > 9 * num) {
            return "";
        }

        string ans = "";

        while (sum > 0) {
            int digit = min(9, sum);
            ans += char('0' + digit);
            sum -= digit;
        }

        while (ans.size() < num) {
            ans += '0';
        }

        return ans;
    }
};
