#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findDup(int len, const string &s) {
        if (len == 0) return -1;

        const long long p = 31, mod = 1e9 + 9;
        int n = s.size();

        vector<long long> p_pow(n, 1), h(n + 1, 0);
        for (int i = 1; i < n; i++) p_pow[i] = (p_pow[i - 1] * p) % mod;
        for (int i = 0; i < n; i++) h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % mod;

        unordered_map<long long, vector<int>> seen;
        for (int i = 0; i + len <= n; i++) {
            long long cur = (h[i + len] - h[i] + mod) % mod;
            cur = (cur * p_pow[n - i - len]) % mod;

            if (seen.count(cur)) {
                for (int j : seen[cur])
                    if (s.compare(i, len, s, j, len) == 0)
                        return i;
            }
            seen[cur].push_back(i);
        }
        return -1;
    }

    string longestDupSubstring(string s) {
        int n = s.size(), L = 1, R = n - 1, best = 0, pos = -1;
        while (L <= R) {
            int mid = (L + R) / 2, found = findDup(mid, s);
            if (found != -1) {
                best = mid; pos = found;
                L = mid + 1;
            } else R = mid - 1;
        }
        return pos == -1 ? "" : s.substr(pos, best);
    }
};
//sghg