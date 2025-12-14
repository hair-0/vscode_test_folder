//谁做了好事2 http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1389&pid=2547&isOOP=false
#include <iostream>

using namespace std;

int main() {
    for (char wiper = 'A'; wiper <= 'E'; wiper++) {
        for (char finder = 'A'; finder <= 'E'; finder++) {
            if (wiper == finder) {
                continue;
            }

            int a_score = (wiper != 'A') + (finder == 'C');
            int b_score = (wiper == 'D') + (finder != 'E');
            int c_score = (wiper == 'B') + (finder != 'A');

            bool d_stmt1 = (wiper != 'A' && wiper != 'B' && finder != 'A' && finder != 'B');
            int d_score = d_stmt1 + (wiper != 'C');

            bool e_stmt1 = (finder == 'D' || wiper == 'E');
            int e_score = e_stmt1 + (wiper != 'A');

            if (a_score == 1 && b_score == 1 && c_score == 1 && d_score == 1 && e_score == 1) {
                cout << wiper << endl;
                cout << finder << endl;
                return 0;
            }
        }
    }

    return 0;
}