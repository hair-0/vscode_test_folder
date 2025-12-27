//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1392&pid=2592&isOOP=false
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

struct WordNode {
    string word;
    int count;
};

bool compareWords(const WordNode& a, const WordNode& b) {
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.word < b.word;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) return 0;

    map<string, int> dict;
    string currentWord = "";
    char c;

    while (fin.get(c)) {
        if (isalpha(static_cast<unsigned char>(c))) {
            currentWord += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        } else {
            if (!currentWord.empty()) {
                dict[currentWord]++;
                currentWord = "";
            }
        }
    }
    if (!currentWord.empty()) {
        dict[currentWord]++;
    }

    vector<WordNode> vec;
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        WordNode node;
        node.word = it->first;
        node.count = it->second;
        vec.push_back(node);
    }

    sort(vec.begin(), vec.end(), compareWords);

    for (size_t i = 0; i < vec.size(); ++i) {
        fout << vec[i].word << " " << vec[i].count << endl;
    }

    fin.close();
    fout.close();

    return 0;
}