#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll get_hash(int l, int r, const vector<ll>& h, const vector<ll>& p_pow, ll mod, int n) {
    ll res = (h[r + 1] - h[l] + mod) % mod;
    return (res * p_pow[n - l]) % mod;
}

int main() {
    string s, t;
    int k;
    cin >> s >> t >> k;

    int n = s.size();
    vector<int> bad(n + 1, 0);
    for (int i = 0; i < n; i++)
        bad[i + 1] = bad[i] + (t[s[i] - 'a'] == '0');

    const ll mod = 1e9 + 9, p = 31;
    vector<ll> p_pow(n + 1, 1), h(n + 1, 0);
    for (int i = 1; i <= n; i++) p_pow[i] = p_pow[i - 1] * p % mod;
    for (int i = 0; i < n; i++) h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % mod;

    unordered_set<ll> seen;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (bad[j + 1] - bad[i] > k) break;
            seen.insert(get_hash(i, j, h, p_pow, mod, n));
        }
    }

    cout << seen.size();
}
