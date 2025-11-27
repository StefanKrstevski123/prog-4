#include <bits/stdc++.h>
using namespace std;

vector<int> rabin_karp(string &text, string &pattern) {
    const int p = 31;          // baza na presmetuvanje na hesh
    const int mod = 1e9 + 9;   // golem prest modul za da se izzbegne overflow

    int n = text.size();
    int m = pattern.size();

    // vektor so prethodno presmetani stepeni p (p^0, p^1, p^2, ...)
    vector<long long> p_pow(max(n, m));
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % mod;

    // prefisni heshovi za tekstot
    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (text[i] - 'a' + 1) * p_pow[i]) % mod;

    // Hesh na patternot
    long long hash_pattern = 0;
    for (int i = 0; i < m; i++)
        hash_pattern = (hash_pattern + (pattern[i] - 'a' + 1) * p_pow[i]) % mod;

    vector<int> positions;

    for (int i = 0; i + m <= n; i++) {
        long long cur_h = (h[i + m] - h[i] + mod) % mod;

        if (cur_h == (hash_pattern * p_pow[i]) % mod) {
            positions.push_back(i);
        }
    }

    return positions;
}

int main() {
    string text, pattern;
    cout << "Внеси текст: ";
    cin >> text;
    cout << "Внеси збор: ";
    cin >> pattern;

    vector<int> result = rabin_karp(text, pattern);

    if (result.empty()) {
        cout << "Нема пронајдени појави на шаблонот во текстот.\n";
    } else {
        cout << "Patternot не е пронајден " << result.size() << " пати, на позиции: ";
        for (int idx : result)
            cout << idx + 1 << " ";
        cout << endl;
    }

    return 0;
}
