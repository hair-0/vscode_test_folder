//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1396&pid=1525&isOOP=false
//(LIS)问题，最长不下降子序列 问题变种

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    int m;
    cin >> m;

    if (m == 0) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> dp(n, 1);
        int ans = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (h[i] >= h[j]) dp[i] = max(dp[i], dp[j] + 1);
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
        return 0;
    }

    vector<int> must(m);
    for (int i = 0; i < m; i++) cin >> must[i];

    long long total = 0;
    vector<int> dp(n);

    int p1_end = must[0];
    fill(dp.begin(), dp.end(), 1);
    for (int i = 0; i <= p1_end; i++) {
        for (int j = 0; j < i; j++) {
            if (h[i] >= h[j]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    total += dp[p1_end];

    for (int k = 0; k < m - 1; k++) {
        int u = must[k];
        int v = must[k + 1];
        
        fill(dp.begin(), dp.end(), 0);
        dp[u] = 1;

        for (int i = u + 1; i <= v; i++) {
            for (int j = u; j < i; j++) {
                if (dp[j] > 0 && h[i] >= h[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        total += (dp[v] - 1);
    }

    int last = must[m - 1];
    fill(dp.begin(), dp.end(), 0);
    dp[last] = 1;
    int max_tail = 1;

    for (int i = last + 1; i < n; i++) {
        for (int j = last; j < i; j++) {
            if (dp[j] > 0 && h[i] >= h[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_tail = max(max_tail, dp[i]);
    }
    total += (max_tail - 1);

    cout << total << endl;

    return 0;
}
