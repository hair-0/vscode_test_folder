//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1389&pid=2572&isOOP=false
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end(), greater<int>());

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << arr[k - 1] << " ";
    }
    cout << endl;

    return 0;
}