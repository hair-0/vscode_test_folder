#include <iostream>
using namespace std;

int main() {
    int n;
    std::cin >> n;

    long long sum = 0;
    int count = 0;
    bool found_minus_one = false;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        if (x == -1) {
            found_minus_one = true;
            continue;
        }

        bool condition1 = (x % 3 == 0 || x % 5 == 0);
        bool condition2 = x < 1000;
        bool condition3 = !found_minus_one;
        bool condition4 = count < 10;

        if (condition1 && condition2 && condition3 && condition4) {
            sum += x;
            count++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}