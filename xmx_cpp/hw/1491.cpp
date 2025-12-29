//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1400&pid=1491&isOOP=false
//动态规划问题DP

#include <iostream>
#include <algorithm> // 用于使用 min 函数
#include <vector>

using namespace std;

// 定义稍微大一点的数组大小，防止越界
const int MAXN = 1005;
const int INF = 1e9; // 一个很大的数，代表无穷大

// dp[i][j] 存储到达 (i, j) 的最小时间
int dp[MAXN][MAXN];
// h[i][j] 存储从 (i,j) 到 (i+1,j) 的时间
int h[MAXN][MAXN];
// v[i][j] 存储从 (i,j) 到 (i,j+1) 的时间
int v[MAXN][MAXN];

int main() {
    // 题目提示：关闭同步流以加快 cin/cout 速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 1. 读取 h 矩阵 (n行 m+1列)
    // 这里的 h[i][j] 代表从第 i 行走到第 i+1 行，在第 j 列的花费
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> h[i][j];
        }
    }

    // 2. 读取 v 矩阵 (n+1行 m列)
    // 这里的 v[i][j] 代表从第 j 列走到第 j+1 列，在第 i 行的花费
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    // 3. 动态规划计算
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // 起点时间为 0
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
                continue;
            }

            // 初始化当前点为无穷大
            long long cost_from_top = INF;
            long long cost_from_left = INF;

            // 尝试从上面 (i-1, j) 走下来
            if (i > 0) {
                // h[i-1][j] 正是 (i-1, j) -> (i, j) 的花费
                cost_from_top = dp[i - 1][j] + h[i - 1][j];
            }

            // 尝试从左边 (i, j-1) 走过来
            if (j > 0) {
                // v[i][j-1] 正是 (i, j-1) -> (i, j) 的花费
                cost_from_left = dp[i][j - 1] + v[i][j - 1];
            }

            // 取两者较小值
            dp[i][j] = min(cost_from_top, cost_from_left);
        }
    }

    // 4. 输出到达 (n, m) 的结果
    cout << dp[n][m] << endl;

    return 0;
}
