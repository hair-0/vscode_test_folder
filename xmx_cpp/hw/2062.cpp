#include <iostream>

int a1 = 0;
int a2 = 0;

int max2(int x) {
    if (x > a1) {
        a2 = a1;
        a1 = x;
    } else if (x > a2) {
        a2 = x;
    }
    return a2;
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int current_num;
        std::cin >> current_num;
        max2(current_num);
    }
    
    std::cout << a2 << std::endl;
    
    return 0;
}