Number of Sets of K Non-Overlapping Line Segments
Problem Statement
Given n points on a 1-D number line (labeled 0 to n-1), count how many distinct ways there are to draw exactly k non-overlapping line segments such that:

Each segment connects two points (its endpoints must be points from the n given points, and can coincide — a segment can have zero length).
Two segments are considered overlapping if they share a point, except two segments are allowed to share an endpoint (e.g., [0,2] and [2,4] are not overlapping).
Order of segments doesn't matter; only the resulting set of segments matters.
Return the number of ways, modulo 1e9 + 7.

This is LeetCode 1621, Number of Sets of K Non-Overlapping Line Segments.

Key Insight: Reformulating as a Combinatorics Problem
The direct way to think about "k non-overlapping segments on n points" is hard to count combinatorially because segments can touch at endpoints and can have zero length. The standard trick is a stars-and-bars transformation.

Step 1 — Represent each segment by its two endpoints
A set of k non-overlapping segments uses 2k "endpoint slots" in total, and these 2k slots, read left to right, must be non-decreasing: p_1 <= p_2 <= ... <= p_{2k}, where each pair (p_{2i-1}, p_{2i}) is one segment. The constraint "non-overlapping" (touching allowed) is exactly captured by this non-decreasing ordering — segment i must end at or before segment i+1 begins.

So the problem reduces to: how many non-decreasing sequences of length 2k can be chosen from the n values {0, 1, ..., n-1}?

Step 2 — Counting non-decreasing sequences = counting multisets
Choosing a non-decreasing sequence of length 2k from n possible values is the same as choosing a multiset of size 2k from n elements (order is then forced by sorting). The number of multisets of size m from n elements is the classic "combinations with repetition" formula:

C(n + m - 1, m)
Substituting m = 2k, the answer is:

C(n + k - 1, 2k)
This is exactly what numberOfSets(n, k) computes.

Code Walkthrough
long long numberOfSets(int n, int k) {
    return combination(n + k - 1, 2 * k);
}
This single line applies the formula above directly: C(n + k - 1, 2k).

combination(n, r) — computing nCr mod p
long long combination(int n, int r) {
    if (r < 0 || r > n)
        return 0;

    vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    long long numerator = fact[n];
    long long denominator = fact[r] * fact[n - r] % MOD;

    return numerator * modPow(denominator, MOD - 2) % MOD;
}
Since n and r can make nCr astronomically large, everything is computed modulo MOD = 1e9 + 7, a prime. The steps are:

Bounds check: if r is negative or bigger than n, there are zero ways — return 0 immediately.
Factorial table: build fact[i] = i! mod MOD for all i from 0 to n, using a bottom-up loop. Each entry is built from the previous one: fact[i] = fact[i-1] * i % MOD.
Apply the formula nCr = n! / (r! * (n-r)!). Since we're working in modular arithmetic, division isn't defined the normal way — you can't just divide two numbers mod a prime. Instead, division by x is replaced by multiplication by the modular inverse of x.
modPow(a, b) — fast exponentiation for the modular inverse
long long modPow(long long a, long long b) {
    long long result = 1;
    while (b > 0) {
        if (b & 1)
            result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}
This computes a^b mod MOD using binary exponentiation (also called fast/exponentiation by squaring), which runs in O(log b) multiplications instead of O(b):

At each step, check the lowest bit of b. If it's 1, fold the current power of a into result.
Square a and shift b right by one bit, repeating until b becomes 0.
The modular inverse of denominator is obtained via Fermat's Little Theorem: since MOD is prime and denominator is not a multiple of MOD, we have:

denominator^(MOD - 1) ≡ 1 (mod MOD)
=> denominator^(MOD - 2) ≡ denominator^(-1) (mod MOD)
So modPow(denominator, MOD - 2) gives exactly the value that "division by denominator" corresponds to under modular arithmetic. Multiplying numerator by this inverse is equivalent to numerator / denominator.

Complexity Analysis
Let N = n + k - 1 be the larger argument passed into combination.

Time complexity: O(N + log MOD)
Building the factorial table takes O(N).
Computing the modular inverse via modPow takes O(log MOD), which is effectively a constant (~30 iterations since MOD ≈ 10^9).
Space complexity: O(N) for the factorial table.
Since LeetCode's constraints for this problem are small (n, k <= 1000), this comfortably runs in well under the time limit.

Worked Example
Take n = 4, k = 2:

We need C(n + k - 1, 2k) = C(4 + 2 - 1, 4) = C(5, 4).
C(5, 4) = 5.
So there are 5 ways to draw 2 non-overlapping segments using points 0, 1, 2, 3. Listing them confirms this: [0,0][1,1]... and so on for all valid non-decreasing quadruples of endpoints — 5 in total, matching the formula.
Edge Cases Handled
Case	Behavior
r > n in combination	Returns 0 — correctly handles cases where you can't even choose 2k "slots" from the available range.
r < 0	Returns 0 — defensive check, shouldn't occur given valid n, k inputs but guards against misuse.
denominator ≡ 0 (mod MOD)	Not handled — but since MOD is a large prime and n <= ~2000 in practice, fact[r] and fact[n-r] are never 0 mod MOD for these constraints, so this isn't a practical concern here.
Zero-length segments	Implicitly allowed by the model — a segment [p, p] is valid since the endpoint sequence only needs to be non-decreasing, not strictly increasing.
Why This Approach Is Correct (Summary)
The problem "count sets of k non-overlapping segments from n points" is transformed into "count non-decreasing sequences of length 2k drawn from n values," which is a textbook stars-and-bars / combinations-with-repetition problem, solved by C(n + k - 1, 2k). The rest of the code is pure modular-arithmetic machinery (factorials + Fermat's Little Theorem + fast exponentiation) needed to compute that one binomial coefficient efficiently and safely under a large modulus.
