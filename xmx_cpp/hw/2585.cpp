#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream inputFile("clues_and_plays.txt");
    vector<string> fileLines;
    string line;

    while (getline(inputFile, line) && fileLines.size() < 1000) {
        fileLines.push_back(line);
    }
    inputFile.close();

    if (fileLines.empty()) return 0;

    int N = stoi(fileLines[0]);
    if (N < 1 || N > 10) return 0;

    vector<vector<int>> clues;
    for (int i = 1; i <= N && i < fileLines.size(); ++i) {
        stringstream ss(fileLines[i]);
        int m, n, k;
        if (ss >> m >> n >> k) {
            if (m >= (N + 2) && m <= 1000 && n >= 1 && n <= 100 && k >= 1 && k <= 10) {
                clues.push_back({m, n, k});
            }
        }
    }

    ofstream outputFile("secret_message.txt");
    for (size_t i = 0; i < clues.size(); ++i) {
        int lineIdx = clues[i][0] - 1;
        int colIdx = clues[i][1] - 1;
        int len = clues[i][2];

        string extractedStr;
        if (lineIdx >= 0 && lineIdx < fileLines.size()) {
            const string& targetLine = fileLines[lineIdx];
            for (int j = 0; j < len; ++j) {
                int pos = colIdx + j;
                if (pos >= 0 && pos < targetLine.length()) {
                    extractedStr += targetLine[pos];
                } else {
                    extractedStr += '*';
                }
            }
        } else {
            extractedStr.append(len, '*');
        }

        outputFile << extractedStr;
        if (i < clues.size() - 1) {
            outputFile << " ";
        }
    }

    outputFile.close();
    return 0;
}
