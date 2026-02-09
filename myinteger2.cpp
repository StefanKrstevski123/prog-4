#include <bits/stdc++.h>
using namespace std;



string stripZeros(const string& s) {
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') i++;
    return s.substr(i);
}


struct BigInt {
    string num;

    BigInt() : num("0") {}
    BigInt(const string& s) : num(stripZeros(s)) {}
    BigInt(const char* s) : num(stripZeros(string(s))) {}

    BigInt& operator=(const BigInt& other) {
        if (this != &other) num = other.num;
        return *this;
    }
};


ostream& operator<<(ostream& os, const BigInt& a) {
    os << a.num;
    return os;
}

istream& operator>>(istream& is, BigInt& a) {
    is >> a.num;
    a.num = stripZeros(a.num);
    return is;
}


int cmp(const BigInt& a, const BigInt& b) {
    if (a.num.size() != b.num.size())
        return a.num.size() < b.num.size() ? -1 : 1;
    if (a.num == b.num) return 0;
    return a.num < b.num ? -1 : 1;
}

bool operator<(const BigInt& a, const BigInt& b) { return cmp(a, b) < 0; }
bool operator>(const BigInt& a, const BigInt& b) { return cmp(a, b) > 0; }
bool operator<=(const BigInt& a, const BigInt& b) { return cmp(a, b) <= 0; }
bool operator>=(const BigInt& a, const BigInt& b) { return cmp(a, b) >= 0; }
bool operator==(const BigInt& a, const BigInt& b) { return cmp(a, b) == 0; }
bool operator!=(const BigInt& a, const BigInt& b) { return cmp(a, b) != 0; }


BigInt operator+(const BigInt& a, const BigInt& b) {
    string x = a.num, y = b.num;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string res;
    int carry = 0;

    for (int i = 0; i < max(x.size(), y.size()); i++) {
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

BigInt operator-(const BigInt& a, const BigInt& b) {
    if (a < b) return BigInt("0");

    string x = a.num, y = b.num;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string res;
    int borrow = 0;

    for (int i = 0; i < x.size(); i++) {
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

BigInt operator*(const BigInt& a, const BigInt& b) {
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

BigInt operator/(const BigInt& a, const BigInt& b) {
    if (b.num == "0") throw runtime_error("Division by zero");

    string cur, res;

    for (char c : a.num) {
        cur.push_back(c);
        cur = stripZeros(cur);

        int cnt = 0;
        while (BigInt(cur) >= b) {
            cur = (BigInt(cur) - b).num;
            cnt++;
        }
        res.push_back(cnt + '0');
    }

    return BigInt(res);
}

BigInt operator%(const BigInt& a, const BigInt& b) {
    if (b.num == "0") throw runtime_error("Modulo by zero");

    string cur;
    for (char c : a.num) {
        cur.push_back(c);
        cur = stripZeros(cur);
        while (BigInt(cur) >= b)
            cur = (BigInt(cur) - b).num;
    }
    return BigInt(cur);
}


BigInt binpow(BigInt a, BigInt b) {
    BigInt ZERO("0"), ONE("1"), TWO("2");
    if (b == ZERO) return ONE;

    BigInt half = binpow(a, b / TWO);
    if (b % TWO == ONE)
        return half * half * a;
    return half * half;
}


bool fermatTest(BigInt p) {
    BigInt ZERO("0"), ONE("1"), TWO("2"), THREE("3");
    if (p <= ONE) return false;
    if (p == TWO || p == THREE) return true;
    if (p % TWO == ZERO) return false;

    BigInt a("2");
    if (p <= a) a = "1";
    return binpow(a, p - ONE) % p == ONE;
}

vector<BigInt> dijkstraPrimes(BigInt n) {
    vector<pair<BigInt, BigInt>> pool;
    vector<BigInt> primes;
    BigInt ONE("1"), TWO("2");

    for (BigInt i = TWO; i <= n; i = i + ONE) {
        bool composite = false;
        for (auto& p : pool) {
            while (p.second < i)
                p.second = p.second + p.first;
            if (p.second == i)
                composite = true;
        }
        if (!composite) {
            pool.push_back({i, i * i});
            primes.push_back(i);
        }
    }
    return primes;
}


BigInt modpow(BigInt a, BigInt d, const BigInt& mod) {
    BigInt ZERO("0"), ONE("1"), TWO("2");
    BigInt res("1");
    a = a % mod;

    while (d > ZERO) {
        if (d % TWO == ONE) res = (res * a) % mod;
        a = (a * a) % mod;
        d = d / TWO;
    }
    return res;
}

bool millerTest(const BigInt& a, const BigInt& s, const BigInt& d, const BigInt& n) {
    BigInt ONE("1"), nm1 = n - ONE;
    BigInt x = modpow(a, d, n);
    if (x == ONE || x == nm1) return true;

    for (BigInt i("1"); i < s; i = i + ONE) {
        x = (x * x) % n;
        if (x == nm1) return true;
    }
    return false;
}

bool millerRabin(BigInt n) {
    BigInt ZERO("0"), ONE("1"), TWO("2"), THREE("3");
    if (n <= ONE) return false;
    if (n == TWO || n == THREE) return true;
    if (n % TWO == ZERO) return false;

    BigInt d = n - ONE, s("0");
    while (d % TWO == ZERO) {
        d = d / TWO;
        s = s + ONE;
    }

    vector<BigInt> bases = {
        "2","325","9375","28178",
        "450775","9780504","1795265022"
    };

    for (auto& a : bases) {
        if (a >= n) continue;
        if (!millerTest(a, s, d, n))
            return false;
    }
    return true;
}


int main() {
    BigInt a("2347389234678392345674839234783947389237829467389236782947389");
    BigInt b("3827832738237283723827382372837823");

    cout << a + b << "\n";
    cout << a - b << "\n";
    cout << a * b << "\n";
    cout << a / b << "\n";
    cout << a % b << "\n";

    BigInt n;
    cin >> n;
    for (auto& p : dijkstraPrimes(n))
        cout << p << " ";

    cout << "\n";
    cout << binpow("123", "1090") << "\n";
    cout << fermatTest("5");
}
