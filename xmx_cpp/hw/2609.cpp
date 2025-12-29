//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1400&pid=2609&isOOP=false

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

// 最大地图尺寸
const int MAXN = 26;
int R, C;
char grid[MAXN][MAXN];
// dist[r1][c1][r2][c2] 记录到达该状态的最少步数
// r1,c1 是火人坐标; r2,c2 是冰人坐标
int dist[MAXN][MAXN][MAXN][MAXN];

// 动作方向：原地不动, 上, 下, 左, 右
int dr[] = {0, -1, 1, 0, 0};
int dc[] = {0, 0, 0, -1, 1};

struct State {
    int r1, c1, r2, c2;
};

// 辅助函数：判断字符是否为门 (A-C)
bool is_gate(char c) {
    return c >= 'A' && c <= 'C';
}

// 辅助函数：根据门获取对应的开关字符 (A->a, B->b, C->c)
char get_switch(char gate) {
    return gate + ('a' - 'A');
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> R >> C)) return 0;

    int fr, fc, ir, ic; // 火人和冰人的起始位置

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'F') {
                fr = i; fc = j;
                grid[i][j] = '.'; // 起点视为平地
            } else if (grid[i][j] == 'I') {
                ir = i; ic = j;
                grid[i][j] = '.'; // 起点视为平地
            }
        }
    }

    // 初始化 BFS
    memset(dist, -1, sizeof(dist));
    queue<State> q;
    
    // 初始状态入队
    dist[fr][fc][ir][ic] = 0;
    q.push({fr, fc, ir, ic});

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        int r1 = cur.r1, c1 = cur.c1;
        int r2 = cur.r2, c2 = cur.c2;

        // 检查是否都到达终点 X
        if (grid[r1][c1] == 'X' && grid[r2][c2] == 'X') {
            cout << dist[r1][c1][r2][c2] << endl;
            return 0;
        }

        // 尝试所有可能的移动组合 (5x5 = 25种)
        // i 是火人的动作，j 是冰人的动作
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int nr1 = r1 + dr[i];
                int nc1 = c1 + dc[i];
                int nr2 = r2 + dr[j];
                int nc2 = c2 + dc[j];

                // 1. 基础合法性检查：越界或撞墙
                if (nr1 < 0 || nr1 >= R || nc1 < 0 || nc1 >= C || grid[nr1][nc1] == '#') continue;
                if (nr2 < 0 || nr2 >= R || nc2 < 0 || nc2 >= C || grid[nr2][nc2] == '#') continue;

                // 2. 检查【开关保护规则】 (移动前的状态检查)
                // 规则：若一人在门D上，另一人在开关d上，则在开关d上的人不能移动
                bool move_invalid = false;
                
                // 遍历所有可能的门 A, B, C
                for (char g = 'A'; g <= 'C'; g++) {
                    char s = get_switch(g);
                    
                    // 情况A: 火人在门，冰人在开关 -> 冰人必须不动
                    if (grid[r1][c1] == g && grid[r2][c2] == s) {
                        // 如果冰人动了 (动作索引j != 0)，则非法
                        if (j != 0) { move_invalid = true; break; }
                    }
                    
                    // 情况B: 冰人在门，火人在开关 -> 火人必须不动
                    if (grid[r2][c2] == g && grid[r1][c1] == s) {
                        // 如果火人动了 (动作索引i != 0)，则非法
                        if (i != 0) { move_invalid = true; break; }
                    }
                }
                if (move_invalid) continue;

                // 3. 检查【门通行规则】 (移动过程的检查)
                // 规则：若某人移动起点或终点是门D，则移动前后都必须有人踩在开关d上
                for (char g = 'A'; g <= 'C'; g++) {
                    char s = get_switch(g);

                    // 检查火人是否使用了门 g (起点是g 或 终点是g)
                    bool f_uses = (grid[r1][c1] == g || grid[nr1][nc1] == g);
                    // 检查冰人是否使用了门 g
                    bool i_uses = (grid[r2][c2] == g || grid[nr2][nc2] == g);

                    if (f_uses || i_uses) {
                        // 移动前，是否有人在开关 s 上
                        bool switch_active_old = (grid[r1][c1] == s || grid[r2][c2] == s);
                        // 移动后，是否有人在开关 s 上
                        bool switch_active_new = (grid[nr1][nc1] == s || grid[nr2][nc2] == s);

                        // 只要有一个时刻没人踩开关，这个移动就是非法的
                        if (!switch_active_old || !switch_active_new) {
                            move_invalid = true;
                            break;
                        }
                    }
                }
                if (move_invalid) continue;

                // 4. 更新状态
                if (dist[nr1][nc1][nr2][nc2] == -1) {
                    dist[nr1][nc1][nr2][nc2] = dist[r1][c1][r2][c2] + 1;
                    q.push({nr1, nc1, nr2, nc2});
                }
            }
        }
    }

    // 无法到达
    cout << -1 << endl;
    return 0;
}