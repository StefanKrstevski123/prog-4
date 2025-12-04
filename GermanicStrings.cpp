#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

using ikt = long long;
using u32kt = unsigned int;

vector<ikt> rabin_karp(string& s, string& t) {
    ikt p = 13, mod = 1e9 + 9;
    ikt slen = s.length(), tlen = t.length();
    vector<long long> deg(max(slen, tlen));
    deg[0] = 1;
    for (ikt i = 1; i < max(slen, tlen); i++)
        deg[i] = (deg[i - 1] * p) % mod;

    vector<long long> hash(tlen + 1, 0);
    for (ikt i = 0; i < tlen; i++)
        hash[i + 1] = (hash[i] + (t[i] - 'a' + 1) * deg[i]) % mod;

    long long hash_string = 0;
    for (ikt i = 0; i < slen; i++)
        hash_string = (hash_string + (s[i] - 'a' + 1) * deg[i]) % mod;

    vector<ikt> occurances;
    for (ikt i = 0; i + slen - 1 < tlen; i++) {
        long long cur_h = (hash[i + slen] + mod - hash[i]) % mod;
        if (cur_h == hash_string * deg[i] % mod)
            occurances.push_back(i);
    }
    return occurances;
}

class GermanString {
    u32kt len;
    char data[12];

    bool isShort() const { return len <= 12; }

    char* getPtr() const {
        char* p;
        memcpy(&p, data + 4, sizeof(p));
        return p;
    }

    void setPtr(char* p) { memcpy(data + 4, &p, sizeof(p)); }

public:
    GermanString(const string& s) {
        len = s.size();
        if (isShort()) {
            memcpy(data, s.data(), len);
            if (len < 12) memset(data + len, 0, 12 - len);
        } else {
            memcpy(data, s.data(), 4);
            char* heap = new char[len];
            memcpy(heap, s.data(), len);
            setPtr(heap);
        }
    }

    GermanString(const GermanString& o) {
        len = o.len;
        if (isShort()) memcpy(data, o.data, 12);
        else {
            memcpy(data, o.data, 4);
            char* heap = new char[len];
            memcpy(heap, o.getPtr(), len);
            setPtr(heap);
        }
    }

    GermanString& operator=(const GermanString& o) {
        len = o.len;
        if (isShort()) memcpy(data, o.data, 12);
        else {
            memcpy(data, o.data, 4);
            char* heap = new char[len];
            memcpy(heap, o.getPtr(), len);
            setPtr(heap);
        }
        return *this;
    }

    ~GermanString() { if (!isShort()) delete[] getPtr(); }

    string makeString() const {
        return isShort() ? string(data, len) : string(getPtr(), len);
    }

    ikt getLen() const { return len; }

    char& operator[](ikt index) {
        return isShort() ? data[index] : getPtr()[index];
    }

    bool operator==(const GermanString& o) const {
        if (len != o.len) return false;
        if (memcmp(data, o.data, 4) != 0) return false;
        return isShort()
               ? memcmp(data, o.data, len) == 0
               : memcmp(getPtr(), o.getPtr(), len) == 0;
    }

    char at(ikt ind) { return isShort() ? data[ind] : getPtr()[ind]; }

    GermanString operator+(const GermanString& o) const {
        string temp = this->makeString() + o.makeString();
        return GermanString(temp);
    }

    bool find(string s) {
        string a = this->makeString();
        vector<ikt> occurances = rabin_karp(s, a);
        return !occurances.empty();
    }

    bool find(GermanString s) { return find(s.makeString()); }

    bool empty() const { return len == 0; }

    void clear() {
        if (!isShort()) delete[] getPtr();
        len = 0;
        memset(data, 0, 12);
    }

    friend ostream& operator<<(ostream& os, const GermanString& gs);
};

ostream& operator<<(ostream& os, const GermanString& gs) {
    os << gs.makeString();
    return os;
}

ikt main() {
    GermanString gha("brout");
    cout << gha << '\n';
    string c = "att1";
    GermanString g(c);
    cout << g.at(2) << '\n';
    string txt = "proben tekst", patternT = "proben", patternF = "prboen";
    GermanString gg(txt);
    GermanString cc1(patternT), cc2(patternF);
    GermanString ck = cc1 + cc2;
    cout << ck << '\n';
    bool x = ck == gg, y = ck == ck;
    cout << x << " " << y << '\n';
    cout << ck.getLen() << '\n';
    cout << gg.find(patternT) << " " << gg.find(patternF) << '\n';
    cout << c[1] << '\n';
    c[1] = 'k';
    cout << c << '\n';
    GermanString ng("smt"), nng("short");
    GermanString ng1 = ng, nng1 = nng;
    cout << ng1 << '\n';
    cout << nng1 << '\n';
    ng1 = nng1;
    cout << ng1 << '\n';
    cout << gg.find(nng) << '\n';
    cout << gg.find(cc1);
    return 0;
}
