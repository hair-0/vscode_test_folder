#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <cctype>

using namespace std;

bool isValidInteger(const string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '+' || s[0] == '-') {
        start = 1;
        if (s.length() == 1) return false;
    }
    for (size_t i = start; i < s.length(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile.is_open()) return 0;

    int N, M;
    if (!(inFile >> N >> M)) return 0;

    set<string> allowedCommands;
    for (int i = 0; i < M; ++i) {
        string cmd;
        inFile >> cmd;
        allowedCommands.insert(cmd);
    }

    int K;
    inFile >> K;
    
    string dummy;
    getline(inFile, dummy); 

    for (int i = 0; i < K; ++i) {
        string line;
        getline(inFile, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();

        stringstream ss(line);
        string segment;
        vector<string> tokens;
        while (ss >> segment) {
            tokens.push_back(segment);
        }

        if (tokens.empty()) {
            outFile << "Error" << endl;
            continue;
        }

        string cmd = tokens[0];
        if (allowedCommands.find(cmd) == allowedCommands.end()) {
            outFile << "Error" << endl;
            continue;
        }

        bool isError = false;

        if (cmd == "inbox" || cmd == "outbox") {
            if (tokens.size() != 1) isError = true;
        } 
        else if (cmd == "add" || cmd == "sub" || cmd == "copyto" || cmd == "copyfrom") {
            if (tokens.size() != 2) isError = true;
            else if (!isValidInteger(tokens[1])) isError = true;
            else {
                try {
                    long long val = stoll(tokens[1]);
                    if (val < 0 || val >= N) isError = true;
                } catch (...) {
                    isError = true;
                }
            }
        } 
        else if (cmd == "jump" || cmd == "jumpifzero") {
            if (tokens.size() != 2) isError = true;
            else if (!isValidInteger(tokens[1])) isError = true;
            else {
                try {
                    long long val = stoll(tokens[1]);
                    if (val < 1 || val > K) isError = true;
                } catch (...) {
                    isError = true;
                }
            }
        } 
        else {
            isError = true;
        }

        if (isError) outFile << "Error" << endl;
        else outFile << "OK" << endl;
    }

    inFile.close();
    outFile.close();
    return 0;
}