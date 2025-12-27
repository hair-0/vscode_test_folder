//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1396&pid=2030&isOOP=false
#include <iostream>
#include <algorithm>
using namespace std;

int a[1005][1005];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            a[i][j] += max(a[i + 1][j], a[i + 1][j + 1]);
        }
    }

    cout << a[1][1] << endl;

    return 0;
}
