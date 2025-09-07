class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> finalArr;
        for (int i = 0; i < n / 2; i++) {
            finalArr.push_back(i + 1);
            finalArr.push_back((i + 1) * -1);
        }
        if (finalArr.size() == n) {
            return finalArr;
        }

        finalArr.push_back(0);
        return finalArr;
    }
};