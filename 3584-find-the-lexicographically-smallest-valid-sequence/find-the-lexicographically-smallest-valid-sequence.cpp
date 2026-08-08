class Solution {
public:
    vector<int> validSequence(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        // last[j] = index in word1 used to match word2[j]
        // when we greedily match word2[j...m-1] from the right.
        //
        // In other words, last[j] tells us the position that
        // the suffix word2[j...] needs to start with.
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // -------------------------------------------------------
        // STEP 1: Match word2 from RIGHT to LEFT.
        // -------------------------------------------------------
        //
        // This tells us how much room we need after a candidate
        // index when we use our one allowed mismatch.
        //
        // Example:
        //
        // word1 = b a c d c
        // index = 0 1 2 3 4
        // word2 = a b c
        //
        // From the right:
        // 'c' -> index 4
        // 'b' -> cannot be matched after index 4
        //
        // last[] stores the positions that are possible when
        // matching the suffix greedily from the right.

        while (i >= 0 && j >= 0) {

            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }

            i--;
        }

        // -------------------------------------------------------
        // STEP 2: Greedily build the answer from LEFT to RIGHT.
        // -------------------------------------------------------
        //
        // canSkip = true means we have not used our one allowed
        // character modification yet.
        //
        // Once we choose a mismatching character, canSkip becomes
        // false and all remaining characters must match exactly.

        bool canSkip = true;

        j = 0;

        vector<int> ans;

        for (i = 0; i < n; i++) {

            // We already selected all required characters.
            if (j == m)
                break;

            // ---------------------------------------------------
            // CASE 1: Exact match
            // ---------------------------------------------------
            //
            // If word1[i] already equals word2[j], choosing this
            // index is always optimal because we want the
            // lexicographically smallest sequence of indices.

            if (word1[i] == word2[j]) {

                ans.push_back(i);
                j++;
            }

            // ---------------------------------------------------
            // CASE 2: Mismatch
            // ---------------------------------------------------
            //
            // We can use at most ONE mismatch.
            //
            // But before using it, we must make sure that the
            // remaining characters of word2 can still be matched
            // exactly after index i.
            //
            // last[j + 1] tells us where the next character/suffix
            // needs to be placed.
            //
            // Therefore:
            //
            // i < last[j + 1]
            //
            // means there is enough room after i to finish the
            // remaining suffix exactly.

            else if (
                canSkip &&
                (
                    j == m - 1 ||
                    i < last[j + 1]
                )
            ) {

                // Use our one allowed modification.
                canSkip = false;

                ans.push_back(i);
                j++;
            }
        }

        // If we selected all m characters, return the answer.
        // Otherwise, no valid sequence exists.
        if (j == m)
            return ans;

        return {};
    }
};