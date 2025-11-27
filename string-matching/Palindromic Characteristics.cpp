#include <bits/stdc++.h>
using namespace std;

struct Hasher {
    long long p = 31, mod = 1e9 + 9;
    int n;
    vector<long long> pw, h, rh;

    Hasher(string s) {
        n = s.size();
        pw.resize(n + 1);
        h.resize(n + 1);
        rh.resize(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) pw[i] = (pw[i - 1] * p) % mod;

        for (int i = 0; i < n; i++)
            h[i + 1] = (h[i] + (s[i] - 'a' + 1) * pw[i]) % mod;

        reverse(s.begin(), s.end());
        for (int i = 0; i < n; i++)
            rh[i + 1] = (rh[i] + (s[i] - 'a' + 1) * pw[i]) % mod;
    }

    long long get(int l, int r) {
        long long val = (h[r + 1] - h[l] + mod) % mod;
        return (val * pw[n - r - 1]) % mod;
    }

    long long getRev(int l, int r) {
        long long val = (rh[r + 1] - rh[l] + mod) % mod;
        return (val * pw[n - r - 1]) % mod;
    }

    bool isPal(int l, int r) {
        int rl = n - 1 - r, rr = n - 1 - l;
        return get(l, r) == getRev(rl, rr);
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();

    Hasher H(s);
    vector<vector<int>> pc(n, vector<int>(n + 1));
    vector<long long> ans(n + 2);

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            if (!H.isPal(i, j)) continue;

            pc[i][len] = 1;
            int half = len / 2;
            if (half > 0 && H.isPal(i, i + half - 1))
                pc[i][len] = pc[i][half] + 1;

            ans[pc[i][len]]++;
        }
    }

    for (int k = n; k >= 1; k--) ans[k] += ans[k + 1];
    for (int k = 1; k <= n; k++) cout << ans[k] << " ";
    cout << "\n";
}
