#include<iostream>
#include<vector>
using namespace std;

const int max_n = 10000000 + 1;
bool is_squareful[max_n];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    cin >> n;
    for (long long i = 2; i * i <= n; ++i){
        long long square = i * i;
        for (long long j = square; j <= n; j += square){
            is_squareful[j] = true;
        }
    }

int non_squareful_count = 0;
for (int i = 1; i <= n; ++i){
    if (!is_squareful[i]){
        non_squareful_count ++;
    }
}
    cout << non_squareful_count << endl;

    return 0;
}