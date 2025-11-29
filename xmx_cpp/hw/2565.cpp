#include<bits/stdc++.h>
using namespace std;

double Eval_Polynomial(const double a[], int n, double x){
    double count = 0.000;
    for (int i = 0; i < n + 1; i++){
        count += a[i] * pow(x, i);
    }

    return count;
}

int main(){
    double x;
    cin >> x;
    double a[6];
    int n;
    cin >> n;
    for(int i = 0; i < n + 1; i ++) cin >> a[i];

    double res = Eval_Polynomial(a, n, x);
    cout << fixed << setprecision(3) << res << endl;

    return 0;
}