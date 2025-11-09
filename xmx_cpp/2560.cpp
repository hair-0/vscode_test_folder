#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    
    vector<long long> cost(n);
    for (int i = 0; i < n; i++){
        cin >> cost[i];
    }
    if (n == 1){
        cout << 0 << endl;
        return 0;
    }
    if (n == 2){
        cout << min(cost[0],cost[1]) << endl;
        return 0;
    }

    vector<long long> dp(n + 1, 0);

    dp[0] = 0;
    dp[1] = cost[0];

    for (int i = 2; i <= n; i++){
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i -1];
    }

    long long result = min(dp[n - 1], dp[n]);

    cout << result << endl;

    return 0;
}
