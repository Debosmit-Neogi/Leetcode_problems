
class Solution {
public:
    bool canAliceWin(int n) {
        int remove = 10;

        while (n >= remove) {
            n -= remove;
            remove--;

            // Alternate turns
            // Alice wins if Bob cannot make the next move
            if (n < remove) {
                return remove % 2 == 1;
            }
        }

        return false;
    }
};
