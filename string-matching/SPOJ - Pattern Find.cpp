#include <bits/stdc++.h>
using namespace std;

vector<int> rabinKarp(string &text, string &pat) {
    const int p = 13;
    const int mod = 1e9 + 9;
    int n = text.size(), m = pat.size();

    vector<long long> pow(max(n, m));
    pow[0] = 1;
    for (int i = 1; i < (int)pow.size(); i++)
        pow[i] = (pow[i - 1] * p) % mod;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (text[i] - 'a' + 1) * pow[i]) % mod;

    long long patHash = 0;
    for (int i = 0; i < m; i++)
        patHash = (patHash + (pat[i] - 'a' + 1) * pow[i]) % mod;

    vector<int> pos;
    for (int i = 0; i + m <= n; i++) {
        long long cur = (h[i + m] - h[i] + mod) % mod;
        if (cur == (patHash * pow[i]) % mod)
            pos.push_back(i);
    }
    return pos;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string text, pat;
        cin >> text >> pat;

        vector<int> res = rabinKarp(text, pat);
        if (res.empty()) {
            cout << "Not Found\n\n";
        } else {
            cout << res.size() << '\n';
            for (int x : res) cout << x + 1 << " ";
            cout << "\n\n";
        }
    }
    return 0;
}
