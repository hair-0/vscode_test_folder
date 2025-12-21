//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1392&pid=1837&isOOP=false
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> path;

void dfs(int remain, int last) {
    if (remain == 0) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
        return;
    }

    for (int i = min(remain, last); i >= 1; i--) {
        path.push_back(i);
        dfs(remain - i, i);
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n)) return 0;

    dfs(n, n);

    return 0;
}
