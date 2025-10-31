#include<iostream>
using namespace std;

int count_valley(const int a[], int n){
    if (n < 3) return 0;
    int valley_count = 0;

    for (int i = 1; i < n - 1; i++) {
        if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
            valley_count++;
        }
    }
    return valley_count;
}

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];
    cout << count_valley(a,n) << endl;

    return 0;
}