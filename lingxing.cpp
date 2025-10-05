#include <iostream>
#include <string>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;

    int width = 2 * n - 1;

    for (int i = 1; i <= 2 * n - 1; ++i) {
        int num_asterisks;
        int num_spaces;

        if (i <= n) {
            num_asterisks = 2 * i - 1;
            num_spaces = n - i;
        } else {
            num_asterisks = 2 * (2 * n - i) - 1;
            num_spaces = i - n;
        }

        // 输出前导空格
        for (int j = 0; j < num_spaces; ++j) {
            std::cout << " ";
        }

        // 输出星号
        for (int j = 0; j < num_asterisks; ++j) {
            std::cout << "*";
        }

        // 输出后导空格 (保证等宽)
        for (int j = 0; j < num_spaces; ++j) {
            std::cout << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}