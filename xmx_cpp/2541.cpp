#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    if (n == 1){
        cout << 1 << endl;
        return 0;
    }
    if (n == 2){
        cout << 2 << endl;
        return 0;
    }
    if (n == 3){
        cout << 4 << endl;
        return 0;
    }

long long a = 1;
long long b = 2;
long long c = 4;
long long result = 0 ;

for (int i = 4; i <= n; i++){
    result = a + b + c;
    a = b;
    b = c;
    c = result;
}

    cout << result << endl ;
    return 0; 

}