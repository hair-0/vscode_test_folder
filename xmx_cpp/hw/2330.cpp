//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=2330&isOOP=false
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "error" << endl;
        return 0;
    }

    int counts[10] = {0};
    string name;
    int score;

    while (fin >> name >> score) {
        int index = score / 10;
        if (index == 10) {
            index = 9;
        }
        counts[index]++;
    }

    for (int i = 0; i < 10; i++) {
        int len = counts[i];
        if (len > 10) {
            len = 10;
        }
        for (int j = 0; j < 10; j++) {
            if (j < len) {
                fout << "@";
            } else {
                fout << ".";
            }
        }
        fout << endl;
    }

    fin.close();
    fout.close();

    return 0;
}