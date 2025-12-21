//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1392&pid=2345&isOOP=false
#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
bool hasPiece[20][20];
long long dp[20][20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m >> k)) return 0;

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        hasPiece[x][y] = true;
    }

    dp[0][0] = 1;

    int dx[] = {1, 1, 2, 2};
    int dy[] = {2, -2, 1, -1};
    int lx[] = {0, 0, 1, 1};
    int ly[] = {1, -1, 0, 0};

    for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= m; y++) {
            if (dp[x][y] == 0) continue;

            for (int i = 0; i < 4; i++) {
                int tx = x + dx[i];
                int ty = y + dy[i];
                int lpx = x + lx[i];
                int lpy = y + ly[i];

                if (tx <= n && ty >= 0 && ty <= m) {
                    if (!hasPiece[lpx][lpy] && !hasPiece[tx][ty]) {
                        dp[tx][ty] += dp[x][y];
                    }
                }
            }
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}
