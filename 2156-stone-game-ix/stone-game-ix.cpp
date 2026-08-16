class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // Case 1: There are no remainder-1 or remainder-2 stones.
        // Alice can never make the sum non-zero modulo 3 safely.
        if (cnt[1] == 0 && cnt[2] == 0) {
            return false;
        }

        // Case 2: Only one of cnt[1], cnt[2] is zero.
        //
        // Alice must start with the non-zero remainder.
        // After that, players are forced to continue with the same
        // remainder until they eventually need a 0-mod-3 stone.
        //
        // Alice wins iff:
        //   - there are more than 2 such stones, AND
        //   - cnt[0] is odd.
        if (cnt[1] == 0 || cnt[2] == 0) {
            int x = max(cnt[1], cnt[2]);
            return x > 2 && (cnt[0] % 2 == 1);
        }

        // Case 3: Both remainder-1 and remainder-2 stones exist.
        //
        // Alice can choose either side.
        // She wins if the difference between the two groups is
        // greater than 2, OR if cnt[0] is even.
        return abs(cnt[1] - cnt[2]) > 2 || (cnt[0] % 2 == 0);
    }
};