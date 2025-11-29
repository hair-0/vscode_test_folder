/*题目网址
http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1372&pid=2440&isOOP=false
*/
#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int main(){
    string s;
    cin >> s;

    for (int i = 0; i < s.length(); i++){
        if (i % 2 == 0){
            if (s[i] >= 'a' && s[i] <= 'z'){
                s[i] = s[i] - 'a' + 'A';
            }
        }
        else{
            if (s[i] >= '0' && s[i] <= '9'){
                if (s[i] == '9')
                {
                    s[i] = '0';
                }
                else{
                    s[i]++;
                }
            }
        }
    }

    cout << s << endl;
    return 0;
}