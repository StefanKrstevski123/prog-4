//
// Program created by Stefan Krstevski on 12/7/2025
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
using namespace std;

// Struktura za Trie jazol
struct Trie {
    bool end = false;               // oznaka dali e kraj na zbor
    map<string, Trie*> next;        // mapa na deca (klucevi se UTF-8 karakteri)
};

// Funkcija za da go zemi sledniot UTF-8 karakter (rune) od string
string nextRune(const string& s, int& i) {
    unsigned char c = s[i]; // zemi go prviot bajt od karakterot
    int bytes = 1;          // default e 1 bajt (ASCII)

    if ((c & 0xE0) == 0xC0) bytes = 2;   // ako e 2B karakter
    else if ((c & 0xF0) == 0xE0) bytes = 3; // ako e 3B karakter
    else if ((c & 0xF8) == 0xF0) bytes = 4; // ako e 4B karakter

    string r = s.substr(i, bytes); // zemi go celosniot UTF-8 rune
    i += bytes;                    // pomesti go indeksot napred
    return r;                      // vrati go rune-to
}

// Funkcija za vnesuvanje na zbor vo Trie
void insertTrie(Trie* root, const string& word) {
    Trie* cur = root;
    for (int i = 0; i < word.size();) { // UTF-8 iteracija, ne klasicna
        string r = nextRune(word, i);   // zemi go sledniot karakter (rune)
        if (!cur->next.count(r))        // ako nema patekata, kreiraj nov jazol
            cur->next[r] = new Trie();
        cur = cur->next[r];
    }
    cur->end = true; // oznaci kraj na zbor
}

// Funkcija za pecatenje na site zborovi od Trie
void printTrie(Trie* t, string prefix = "") {
    if (t->end) cout << prefix << "\n"; // ako e kraj, pecati go prefiksot (zborot)
    for (auto& kv : t->next)            // pomini gi site deca
        printTrie(kv.second, prefix + kv.first); // rekurzivno dodadi go karakterot
}

int main() {
    // Podesuvanje na konzola za UTF-8 (Windows specificno)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Trie* root = new Trie();

    // Otvori fajl so Makedonski recnik
    ifstream fin("MK.txt");
    if (!fin.is_open()) {
        cerr << "Ne moze da se otvori tekstualniot fajl\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        // Trgni \r ako postoi (Windows fajl format)
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        insertTrie(root, line); // vnesi go zborot vo Trie
    }
    fin.close();

    // Pecati gi site zborovi vo Trie
    printTrie(root);

    return 0;
}
