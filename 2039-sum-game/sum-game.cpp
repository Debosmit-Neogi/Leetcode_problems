class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        // Count digits and '?' in the left half
        for (int i = 0; i < half; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        // Count digits and '?' in the right half
        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        int qDiff = leftQ - rightQ;
        int sumDiff = leftSum - rightSum;

        // Same number of '?' on both sides.
        // Bob can copy Alice's digit on the other side.
        if (qDiff == 0)
            return sumDiff != 0;

        // Odd difference in '?' count means Alice can force
        // the two sums to be different.
        if (abs(qDiff) % 2 == 1)
            return true;

        // If left has more '?':
        // Bob can balance the existing difference only when
        // sumDiff is exactly -9 * (qDiff / 2).
        //
        // If right has more '?', the sign is automatically
        // handled by qDiff.
        int required = -9 * (qDiff / 2);

        return sumDiff != required;
    }
};