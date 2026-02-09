#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    string num;

    BigInt(string s = "0") {
        num = strip(s);
    }

    static string strip(const string& s) {
        int i = 0;
        while (i + 1 < (int)s.size() && s[i] == '0') i++;
        return s.substr(i);
    }

    static int cmp(const string& a, const string& b) {
        string x = strip(a), y = strip(b);
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        if (x == y) return 0;
        return x < y ? -1 : 1;
    }

    friend bool operator>=(const BigInt& a, const BigInt& b) {
        return cmp(a.num, b.num) >= 0;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        string x = a.num, y = b.num;
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());

        string res;
        int carry = 0;

        for (size_t i = 0; i < max(x.size(), y.size()); i++) {
            int d1 = i < x.size() ? x[i] - '0' : 0;
            int d2 = i < y.size() ? y[i] - '0' : 0;
            int sum = d1 + d2 + carry;
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }

        if (carry) res.push_back(carry + '0');
        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        if (cmp(a.num, b.num) < 0) return BigInt("0");

        string x = a.num, y = b.num;
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());

        string res;
        int borrow = 0;

        for (size_t i = 0; i < x.size(); i++) {
            int d1 = x[i] - '0' - borrow;
            int d2 = i < y.size() ? y[i] - '0' : 0;
            if (d1 < d2) {
                d1 += 10;
                borrow = 1;
            } else borrow = 0;
            res.push_back(d1 - d2 + '0');
        }

        reverse(res.begin(), res.end());
        return BigInt(res);
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        if (a.num == "0" || b.num == "0") return BigInt("0");

        vector<int> res(a.num.size() + b.num.size(), 0);

        for (int i = a.num.size() - 1; i >= 0; i--) {
            for (int j = b.num.size() - 1; j >= 0; j--) {
                res[i + j + 1] += (a.num[i] - '0') * (b.num[j] - '0');
            }
        }

        for (int i = res.size() - 1; i > 0; i--) {
            res[i - 1] += res[i] / 10;
            res[i] %= 10;
        }

        string s;
        for (int d : res) s.push_back(d + '0');
        return BigInt(s);
    }

    friend BigInt operator/(const BigInt& a, const BigInt& b) {
        if (b.num == "0") throw runtime_error("Division by zero");

        string cur, res;

        for (char c : a.num) {
            cur.push_back(c);
            cur = strip(cur);

            int q = 0;
            while (cmp(cur, b.num) >= 0) {
                cur = (BigInt(cur) - b).num;
                q++;
            }
            res.push_back(q + '0');
        }

        return BigInt(res);
    }
};

int main() {
    BigInt a("823647389234678392345674839234783947389237829467389236782947389");
    BigInt b("673827832738237283723827382372837823");

    cout << (a + b).num << "\n";
    cout << (a - b).num << "\n";
    cout << (a * b).num << "\n";
    cout << (a / b).num << "\n";
}
