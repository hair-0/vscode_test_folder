//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=2034&isOOP=false
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[105];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        swap(a[i], a[minIndex]);

        cout << "swap(a[" << i << "], a[" << minIndex << "]):";
        for (int k = 0; k < n; k++) {
            if (k > 0) {
                cout << " ";
            }
            cout << a[k];
        }
        cout << endl;
    }

    return 0;
}