class Solution {
public:

    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    long long countAmounts(long long x, vector<int>& coins) {

        int n = coins.size();
        long long count = 0;

        // Try every non-empty subset
        for (int mask = 1; mask < (1 << n); mask++) {

            __int128 lcm = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; i++) {

                if (mask & (1 << i)) {

                    bits++;

                    long long coin = coins[i];

                    long long g =
                        gcd((long long)lcm, coin);

                    lcm = (lcm / g) * coin;

                    // No multiple of this LCM
                    // can be <= x.
                    if (lcm > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge) {
                continue;
            }

            long long contribution =
                x / (long long)lcm;

            if (bits % 2 == 1) {
                count += contribution;
            }
            else {
                count -= contribution;
            }
        }

        return count;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        // Remove duplicate denominations
        sort(coins.begin(), coins.end());
        coins.erase(
            unique(coins.begin(), coins.end()),
            coins.end()
        );

        long long low = 1;

        // The kth answer cannot be greater than
        // the smallest coin multiplied by k.
        long long high =
            (long long)coins[0] * k;

        while (low < high) {

            long long mid =
                low + (high - low) / 2;

            if (countAmounts(mid, coins) >= k) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }

        return low;
    }
};