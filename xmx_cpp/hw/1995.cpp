//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1392&pid=1995&isOOP=false
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    int res[25][25];
    int cur = 1;

    for (int s = 0; s <= 2 * n - 2; s++) {
        if (s % 2 != 0) {
            int r = min(s, n - 1);
            int c = s - r;
            while (r >= 0 && c < n) {
                res[r][c] = cur++;
                r--;
                c++;
            }
        } else {
            int c = min(s, n - 1);
            int r = s - c;
            while (c >= 0 && r < n) {
                res[r][c] = cur++;
                r++;
                c--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << (j == n - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}