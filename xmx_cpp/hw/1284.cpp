//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1396&pid=1284&isOOP=false
//DP 动态规划问题
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long L;
    cin >> n >> L;

    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        sum[i] = sum[i - 1] + x;
    }

    vector<long long> dp(n + 1, 1e18);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            long long current_sum = sum[i] - sum[j];
            long long cost = (current_sum - L) * (current_sum - L);
            
            if (dp[j] + cost < dp[i]) {
                dp[i] = dp[j] + cost;
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}