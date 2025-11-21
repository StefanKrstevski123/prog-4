#include <iostream>
#include <string>
using namespace std;

int substr(const string& s, const string& p) {
    int slen = s.length();
    int plen = p.length();

    for (int i = 0; i <= slen - plen; i++) {
        int j = 0;
        while (j < plen && s[i + j] == p[j]) {
            j++;
        }
        if (j == plen)
            return i; // found match starting at index i
    }
    return -1; // not found
}

int main() {
    string s = "Ova e gimnazija mig";
    string p = "mig";

    int pos = substr(s, p);

    if (pos != -1)
        cout << "The string \"" << p << "\" occurs in position " << pos << "." << endl;
    else
        cout << "The string \"" << p << "\" was not found." << endl;

    return 0;
}
