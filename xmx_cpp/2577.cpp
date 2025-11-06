#include<iostream>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    
    unsigned long long result[65];
    result[1]=1;
    for (int i = 2; i < n+1; i++){
        result[i] = 2*result[i-1] + 1; 
    }
    cout << result[n];

    return 0;
}