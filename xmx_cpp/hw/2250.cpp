//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1396&pid=2250&isOOP=false
//dp动态规划问题，完全背包问题的变种
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<long long> dp(m + 1, -1e18);

    for (int i = 0; i < n; i++) {
        if (a[i] <= m) {
            dp[a[i]] = max(dp[a[i]], (long long)b[i]);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= i / 2; j++) {
            if (dp[j] > -1e17 && dp[i - j] > -1e17) {
                long long val = dp[j] + dp[i - j];
                
                if (j == i - j) {
                    val += 233;
                }
                
                dp[i] = max(dp[i], val);
            }
        }
    }

    cout << dp[m] << endl;

    return 0;
}
