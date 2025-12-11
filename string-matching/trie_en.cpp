#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

// Struktura za Trie jazol
struct Trie {
    Trie* children[26] = {nullptr}; // sekoj jazol moze da ima do 26 deca (a-z)
    bool is_end_word = false;       // dali ovoj jazol e kraj na zbor
    string label = "";              // za Patricia kompresija
};

// Dodavanje zbor vo Trie
void add_to_trie(Trie* root, const string& str) {
    Trie* curr = root;
    for (char ch : str) {
        char c = tolower(ch);               // site bukvi vo mali
        if (c < 'a' || c > 'z') continue;   // preskokni ako ne e bukva

        int ind = c - 'a';                  // presmetaj indeks (0–25)
        if (!curr->children[ind])           // ako nema dete, napravi novo
            curr->children[ind] = new Trie();

        curr = curr->children[ind];         // odi na deteto
    }
    curr->is_end_word = true;               // oznaci kraj na zbor
}

// Konvertiraj Trie vo Patricia trie (kompresija)
void convert_patricia(Trie* node) {
    if (!node) return;

    // Prvo rekurzivno kompresiraj gi site deca
    for (int i = 0; i < 26; i++) {
        if (node->children[i])
            convert_patricia(node->children[i]);
    }

    // Proveri dali jazolot ima tocno edno dete
    int count = 0, index = -1;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            count++;
            index = i;
        }
    }

    // Ako nema tocno edno dete, nema kompresija
    if (count != 1) return;

    Trie* child = node->children[index];

    // Spoj gi label podatocite (kompresija)
    node->label.push_back('a' + index);
    node->label += child->label;

    // Prenesi gi decata i statusot
    for (int i = 0; i < 26; i++)
        node->children[i] = child->children[i];

    node->is_end_word = child->is_end_word;

    delete child; // izbrishi go staroto dete
}

// Pecati gi site zborovi od Trie (nekompresiran)
void print_trie(Trie* node, string& current) {
    if (!node) return;

    if (node->is_end_word)
        cout << current << "\n";

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            current.push_back('a' + i);         // dodadi ja momentalnata bukva
            print_trie(node->children[i], current); // rekurzivno povikaj
            current.pop_back();                 // backtrack
        }
    }
}

// Pecati zborovi od Patricia trie
void print_patricia(Trie* node, string& current) {
    if (!node) return;

    current += node->label; // dodadi label vo momentalniot zbor

    if (node->is_end_word)
        cout << current << "\n";

    for (int i = 0; i < 26; i++) {
        if (node->children[i])
            print_patricia(node->children[i], current);
    }

    // vrati se nazad (backtrack)
    current.erase(current.size() - node->label.size());
}

// Bara zbor vo Trie
bool search_trie(Trie* root, const string& str) {
    Trie* curr = root;
    for (char ch : str) {
        char c = tolower(ch);
        if (c < 'a' || c > 'z') return false;

        int ind = c - 'a';
        if (!curr->children[ind])
            return false;

        curr = curr->children[ind];
    }
    return curr->is_end_word;
}

// Bara zbor vo Patricia trie
bool search_patricia(Trie* node, const string& word, int pos = 0) {
    if (!node) return false;

    int len = node->label.size();
    if (word.size() - pos < len) return false;

    // Sporedi gi bukvite
    for (int i = 0; i < len; i++) {
        if (tolower(word[pos + i]) != node->label[i])
            return false;
    }

    pos += len;
    if (pos == word.size())
        return node->is_end_word;

    char next_char = tolower(word[pos]);
    if (next_char < 'a' || next_char > 'z') return false;

    int ind = next_char - 'a';
    return search_patricia(node->children[ind], word, pos);
}

int main() {
    Trie* root = new Trie();

    // Pateka do tekstualniot fajl so zborovi
    // "C:\Users\Korisnik\OneDrive\Десктоп\wiki-100k.txt"
    string path = "./wiki-100k.txt";
    ifstream txt(path);

    vector<string> words;
    string line;

    // Cita zborovi od fajlot
    while (getline(txt, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        words.push_back(line);
    }

    // Dodadi gi site zborovi vo Trie
    for (const auto& w : words)
        add_to_trie(root, w);

    string temp;

    cout << "--- Trie (Nekomresiran) ---\n";
    print_trie(root, temp);

    // Kompresiraj vo Patricia Trie
    convert_patricia(root);

    cout << "\n--- Patricia Trie (Kompresiran) ---\n";
    print_patricia(root, temp);

    return 0;
}
