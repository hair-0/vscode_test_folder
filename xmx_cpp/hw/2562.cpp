#include<iostream>
using namespace std;

int check_increasing(int a[],int n){
    for (int i = 1; i < n; i++){
        if (a[i-1] >= a[i]){
            return i;
        }
    }
    return 0;
}

int main (){
    int n;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << check_increasing(a, n);
    return 0;
}