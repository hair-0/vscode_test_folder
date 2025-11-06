#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M,N;
    cin >> N >> M;

    bool is_bad[101]={false};

    for (int i = 0; i < M; i++){
        int break_gap;
        cin >> break_gap;
        if (break_gap <= N){
            is_bad[break_gap] = true;
        }
    }

long long dp[101] = {0};
dp[0] = 1;
for (int i = 1; i <= N; ++i){
    if (is_bad[i]){
        dp[i] = 0;
        continue;
    }
    if (i >= 1){
        dp[i] += dp[i-1];
    }
    if (i >= 2){
        dp[i] += dp[i-2];
    }
}
    cout << dp[N] << endl;
    return 0;
}