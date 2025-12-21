//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1392&pid=1687&isOOP=false
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int grid[15][15];
bool col[15], diag1[30], diag2[30];
int max_ans = 0;

void dfs(int r, int count) {
    if (r == n) {
        max_ans = max(max_ans, count);
        return;
    }

    if (count + (n - r) <= max_ans) return;

    for (int c = 0; c < n; c++) {
        if (grid[r][c] == 1 && !col[c] && !diag1[r + c] && !diag2[r - c + n]) {
            col[c] = diag1[r + c] = diag2[r - c + n] = true;
            dfs(r + 1, count + 1);
            col[c] = diag1[r + c] = diag2[r - c + n] = false;
        }
    }

    dfs(r + 1, count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    dfs(0, 0);
    cout << max_ans << endl;

    return 0;
}