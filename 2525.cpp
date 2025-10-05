#include <iostream>
using namespace std;

int main() {
    int num;
    int count = 0, all = 0;

    cin >> num;
    if (num != 0) {
        if (num % 2 == 0) { count++; all += num; }

        cin >> num;
        if (num != 0) {
            if (num % 2 == 0) { count++; all += num; }

            cin >> num;
            if (num != 0) {
                if (num % 2 == 0) { count++; all += num; }

                cin >> num;
                if (num != 0) {
                    if (num % 2 == 0) { count++; all += num; }

                    cin >> num;
                    if (num != 0) {
                        if (num % 2 == 0) { count++; all += num; }
                    }
                }
            }
        }
    }

    cout << count << " " << all << endl;
    return 0;
}
