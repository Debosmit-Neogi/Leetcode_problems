class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        // 1,000 to 999,999 -> 1 comma
        // 1,000,000 to 999,999,999 -> 2 commas
        // 1,000,000,000 onward -> 3 commas
        long long start = 1000;
        long long commas = 1;

        while (start <= n) {
            long long end = std::min(n, start * 1000 - 1);

            ans += (end - start + 1) * commas;

            start *= 1000;
            commas++;
        }

        return ans;
    }
};