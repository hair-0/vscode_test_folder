//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1389&pid=2326&isOOP=false
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, p, q;
    if (!(cin >> m >> p >> q)) return 0;

    vector<int> a(p);
    for (int i = 0; i < p; i++) {
        cin >> a[i];
    }

    vector<int> b(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i];
    }

    long long min_dx = 2000000000;
    int i = 0, j = 0;

    while (i < p && j < q) {
        long long current_diff = abs(a[i] - b[j]);

        if (current_diff < min_dx) {
            min_dx = current_diff;
        }

        if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }

    double ans = sqrt(min_dx * min_dx + 1.0);

    cout << fixed << setprecision(2) << ans << endl;

    return 0;
}