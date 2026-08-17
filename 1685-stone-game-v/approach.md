# Stone Game-V
Stone Game V — Solution Approach

1. Problem Idea

Alice repeatedly splits the current row into two non-empty parts.

For a split:

[l ... k] | [k+1 ... r]

let:

leftSum  = sum(l ... k)
rightSum = sum(k+1 ... r)

Bob removes the part with the larger sum.

Alice gets the sum of the part that remains and continues the game on that remaining part.

If the sums are equal, Alice chooses which part remains.

The goal is to maximize Alice's total score.

2. Key Observation

At any point, the game is completely described by the current subarray.

Therefore, define an interval DP.

dp[l][r]

= maximum score Alice can obtain from stoneValue[l ... r].

If there is only one stone, Alice cannot split it:

dp[l][l] = 0

3. Try Every Split

For every interval [l ... r], try every split position k:

[l ... k] | [k+1 ... r]

There are three cases.

Case 1: leftSum < rightSum

Bob removes the right side.

The left side remains.

Alice gets leftSum and then continues with [l ... k].

dp[l][r] = max(
    dp[l][r],
    leftSum + dp[l][k]
)

Case 2: leftSum > rightSum

Bob removes the left side.

The right side remains.

Alice gets rightSum and then continues with [k+1 ... r].

dp[l][r] = max(
    dp[l][r],
    rightSum + dp[k+1][r]
)

Case 3: leftSum == rightSum

Alice can choose which side remains.

So:

dp[l][r] = max(
    dp[l][r],
    leftSum + max(dp[l][k], dp[k+1][r])
)

4. Prefix Sum

We need to calculate many range sums.

Using a normal loop for every sum would make the solution too slow.

Create:

prefix[i] = sum of the first i elements

Then:

sum(l ... r) = prefix[r + 1] - prefix[l]

Therefore:

int leftSum =
    prefix[k + 1] - prefix[l];

int rightSum =
    prefix[r + 1] - prefix[k + 1];

Each range sum is now O(1).

5. DP Order

dp[l][r] depends on smaller intervals:

dp[l][k]
dp[k+1][r]

Therefore, process intervals by increasing length:

for (int len = 2; len <= n; len++)

For example:

Length 1:
[0] [1] [2] ...

Length 2:
[0,1] [1,2] [2,3] ...

Length 3:
[0,2] [1,3] ...

...

By the time we calculate dp[l][r], all required smaller intervals have already been calculated.

6. Complete C++ Solution

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // prefix[i] = sum of first i elements
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        // dp[l][r] = maximum score Alice can get
        // from subarray [l ... r]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Process intervals from smaller to larger
        for (int len = 2; len <= n; len++) {

            for (int l = 0; l + len <= n; l++) {

                int r = l + len - 1;

                // Try every possible split
                for (int k = l; k < r; k++) {

                    int leftSum =
                        prefix[k + 1] - prefix[l];

                    int rightSum =
                        prefix[r + 1] - prefix[k + 1];

                    if (leftSum < rightSum) {

                        // Bob removes the right side.
                        // Alice keeps the left side.
                        dp[l][r] = max(
                            dp[l][r],
                            leftSum + dp[l][k]
                        );

                    }
                    else if (leftSum > rightSum) {

                        // Bob removes the left side.
                        // Alice keeps the right side.
                        dp[l][r] = max(
                            dp[l][r],
                            rightSum + dp[k + 1][r]
                        );

                    }
                    else {

                        // Equal sums:
                        // Alice chooses which side remains.
                        dp[l][r] = max(
                            dp[l][r],
                            leftSum + max(
                                dp[l][k],
                                dp[k + 1][r]
                            )
                        );
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
};

7. Dry Run

Consider:

stoneValue = [6, 2, 3, 4, 5, 5]

A useful first split is:

[6, 2, 3] | [4, 5, 5]

Sums:

leftSum  = 11
rightSum = 14

Since:

11 < 14

Bob removes the right side.

Alice gets:

11

The remaining problem is:

[6, 2, 3]

Split:

[6] | [2, 3]

Sums:

6
5

Bob removes [6].

Alice gets:

5

Remaining:

[2, 3]

Split:

[2] | [3]

Bob removes [3].

Alice gets:

2

Total:

11 + 5 + 2 = 18

So the answer is:

18

8. Why Greedy Does Not Work

We cannot simply choose the split that gives Alice the largest immediate score.

For example:

Split A:
current score = 10
future score  = 2
total         = 12

while another split could be:

Split B:
current score = 7
future score  = 10
total         = 17

So Alice must consider:

current score + best future score

This is exactly what the DP state represents.

9. Why This Is Interval DP

The general pattern is:

Choose interval [l, r]
        |
        v
Try every split k
        |
        v
Calculate leftSum and rightSum
        |
        v
Determine which side survives
        |
        v
Add current score
        |
        v
Use DP of the surviving interval

The important state is:

dp[l][r]

and the important decision is:

split at k

This is a classic interval-DP structure.

10. Complexity

There are O(n²) possible intervals.

For each interval, we try O(n) split positions.

Therefore:

Time Complexity:  O(n³)
Space Complexity: O(n²)

Prefix sums use O(n) extra space, which is dominated by the O(n²) DP table.

11. Final Pattern to Remember

When you see a problem where:

You have a contiguous interval.

You can split the interval.

The result depends on the two sides.

The game continues on one of the resulting intervals.

Think:

dp[l][r]

Then:

for every split k:
    calculate leftSum
    calculate rightSum

    if leftSum < rightSum:
        use left side

    else if leftSum > rightSum:
        use right side

    else:
        choose the better side

The core formula is:

current score + best score from the remaining interval
