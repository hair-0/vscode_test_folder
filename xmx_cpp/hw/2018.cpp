#include <iostream>
using namespace std;

int main() {
    int a, b;
    
    if (std::cin >> a >> b) {
        for (int i = 1; i <= a; ++i) {
            for (int j = 1; j <= b; ++j) {
                if (i == 1 || i == a || j == 1 || j == b) {
                    std::cout << "*";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}