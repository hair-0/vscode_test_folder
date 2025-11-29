#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    if (n == 1){
        cout << 0 << endl;
        return 0;
    }
    if (n == 2){
        cout << 1 << endl;
        return 0;
    }

    long long dp[21] = {0};
    dp[1] = 0;
    dp[2] = 1;
    
    for (int i = 3; i <= n; i++){
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }

    cout << dp[n] << endl;

    return 0;
}