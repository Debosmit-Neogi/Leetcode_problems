class Solution {
public:
    // digit -> (exp2, exp3, exp5, exp7)
    int dexp[10][4] = {
        {0,0,0,0}, // 0 (unused)
        {0,0,0,0}, // 1
        {1,0,0,0}, // 2
        {0,1,0,0}, // 3
        {2,0,0,0}, // 4
        {0,0,1,0}, // 5
        {1,1,0,0}, // 6
        {0,0,0,1}, // 7
        {3,0,0,0}, // 8
        {0,2,0,0}, // 9
    };

    int E2, E3, E5, E7;
    int bz, cz, dz; // strides for flattened index
    vector<int> f;  // f[idx4(a,b,c,d)] = min digits to satisfy (a,b,c,d)
    const int INF = 1e9;

    inline int idx4(int a, int b, int c, int d) {
        return a * bz + b * cz + c * dz + d;
    }

    string buildSuffix(int a, int b, int c, int d, int L) {
        string res;
        res.reserve(L);
        int ra = a, rb = b, rc = c, rd = d;
        for (int pos = 0; pos < L; pos++) {
            int remaining = L - pos - 1;
            for (int dig = 1; dig <= 9; dig++) {
                int na = max(0, ra - dexp[dig][0]);
                int nb = max(0, rb - dexp[dig][1]);
                int nc = max(0, rc - dexp[dig][2]);
                int nd = max(0, rd - dexp[dig][3]);
                if (f[idx4(na, nb, nc, nd)] <= remaining) {
                    res.push_back('0' + dig);
                    ra = na; rb = nb; rc = nc; rd = nd;
                    break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        int n = num.size();

        // ---- 1. factor t into 2^E2 * 3^E3 * 5^E5 * 7^E7 * (rest) ----
        long long tt = t;
        int primes[4] = {2, 3, 5, 7};
        int e[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; i++) {
            while (tt % primes[i] == 0) {
                tt /= primes[i];
                e[i]++;
            }
        }
        if (tt != 1) return "-1";
        E2 = e[0]; E3 = e[1]; E5 = e[2]; E7 = e[3];

        // ---- 2. build f table ----
        dz = E7 + 1;
        cz = (E5 + 1) * dz;
        bz = (E3 + 1) * cz;
        int size = (E2 + 1) * bz;
        f.assign(size, INF);
        f[idx4(0, 0, 0, 0)] = 0;

        for (int a = 0; a <= E2; a++) {
            for (int b = 0; b <= E3; b++) {
                for (int c = 0; c <= E5; c++) {
                    for (int d = 0; d <= E7; d++) {
                        if (a == 0 && b == 0 && c == 0 && d == 0) continue;
                        int best = INF;
                        for (int dig = 2; dig <= 9; dig++) {
                            int na = max(0, a - dexp[dig][0]);
                            int nb = max(0, b - dexp[dig][1]);
                            int nc = max(0, c - dexp[dig][2]);
                            int nd = max(0, d - dexp[dig][3]);
                            int val = f[idx4(na, nb, nc, nd)];
                            if (val + 1 < best) best = val + 1;
                        }
                        f[idx4(a, b, c, d)] = best;
                    }
                }
            }
        }

        // ---- 3. prefix cumulative exponents of num ----
        vector<array<int,4>> prefix(n + 1, {0,0,0,0});
        for (int i = 0; i < n; i++) {
            int dgt = num[i] - '0';
            prefix[i+1] = prefix[i];
            if (dgt >= 1 && dgt <= 9) {
                for (int k = 0; k < 4; k++) prefix[i+1][k] += dexp[dgt][k];
            }
        }

        auto reqAt = [&](int k) -> array<int,4> {
            array<int,4> r;
            r[0] = max(0, E2 - prefix[k][0]);
            r[1] = max(0, E3 - prefix[k][1]);
            r[2] = max(0, E5 - prefix[k][2]);
            r[3] = max(0, E7 - prefix[k][3]);
            return r;
        };

        int z = -1;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') { z = i; break; }
        }
        if (z == -1) z = n;

        // ---- 4. num itself already works? ----
        if (z == n) {
            auto r = reqAt(n);
            if (r[0] == 0 && r[1] == 0 && r[2] == 0 && r[3] == 0) return num;
        }

        // ---- 5. bump at latest possible position (same length) ----
        int hi = min(z, n - 1);
        for (int i = hi; i >= 0; i--) {
            auto req = reqAt(i);
            int start_d = (i == z) ? 1 : (num[i] - '0') + 1;
            int remaining_len = n - i - 1;
            for (int dig = start_d; dig <= 9; dig++) {
                int na = max(0, req[0] - dexp[dig][0]);
                int nb = max(0, req[1] - dexp[dig][1]);
                int nc = max(0, req[2] - dexp[dig][2]);
                int nd = max(0, req[3] - dexp[dig][3]);
                if (f[idx4(na, nb, nc, nd)] <= remaining_len) {
                    string suffix = buildSuffix(na, nb, nc, nd, remaining_len);
                    return num.substr(0, i) + char('0' + dig) + suffix;
                }
            }
        }

        // ---- 6. need more digits than num has ----
        int F = f[idx4(E2, E3, E5, E7)];
        int L = max(n + 1, F);
        return buildSuffix(E2, E3, E5, E7, L);
    }
};