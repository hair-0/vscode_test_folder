#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    getline(cin, s);
    
    string filtered;
    for (char c : s) {
        if (isalnum(c)) {
            filtered += tolower(c);
        }
    }
    
    int left = 0, right = filtered.length() - 1;
    while (left < right) {
        if (filtered[left] != filtered[right]) {
            cout << 0;
            return 0;
        }
        left++;
        right--;
    }
    
    cout << 1;
    return 0;
}