#include<iostream>
#include<string>
#include<cctype>
using namespace std;

//我在这道题直接调用了cctype库中处理字符的函数，可以简化代码
int main(){
    std::string s;
    std::cin >> s;

    for (int i = 0; i <= s.length(); ++i){
        if (i % 2 == 0){
            if (islower(s[i])){
                s[i] = toupper(s[i]);
            }
        }
        else{
            if (isdigit(s[i])){
                if (s[i] == '9'){
                    s[i] == '0';
                }
                else{
                    s[i] = s[i] + 1;
                }
            }
        }
    }

    std::cout << s << std::endl;
    return 0;
}