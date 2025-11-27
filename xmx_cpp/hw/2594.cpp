//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1383&pid=2594&isOOP=false
//之前N 过大时采用了 O(N) 的遍历方法，导致超时。现改为构造回文数的 O(sqrt(N​)) 方法，可以成功避免超时
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

long long N; 

int count_palindromes() {
    int palindrome_count = 0;
    long long max_half = 100000; 

    for (long long k = 1; k < max_half; ++k) {
        string s = to_string(k);
        string s_rev = s;
        reverse(s_rev.begin(), s_rev.end());

        // 奇数位回文数
        string odd_palindrome_str = s + s_rev.substr(1);
        long long odd_palindrome;

        try {
            odd_palindrome = stoll(odd_palindrome_str);
        } catch (const std::out_of_range& e) {
            // 如果超出 long long 范围，则 break
            break; 
        }

        if (odd_palindrome <= N) {
            palindrome_count++;
        }
        
        // 偶数位回文数
        string even_palindrome_str = s + s_rev;
        long long even_palindrome;

        try {
            even_palindrome = stoll(even_palindrome_str);
        } catch (const std::out_of_range& e) {
            // 如果超出 long long 范围，则 break
            break; 
        }

        if (even_palindrome <= N) {
            palindrome_count++;
        } 
        
        if (even_palindrome > N && odd_palindrome > N && s.length() == to_string(max_half - 1).length()) {
             // 如果当前长度的回文数都超出了 N，且 k 已经是该长度的最大值，可以提前退出。
        }
    }

    return palindrome_count;
}

void solve() {
    if (!(cin >> N)) return; 

    // 统计完美数
    const vector<long long> perfect_numbers = {6, 28, 496, 8128, 33550336LL};
    
    int perfect_count = 0;
    for (long long p : perfect_numbers) {
        if (p <= N) {
            perfect_count++;
        } else {
            break; 
        }
    }
    
    // 统计回文数
    int palindrome_count = count_palindromes();


    cout << perfect_count << " " << palindrome_count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}