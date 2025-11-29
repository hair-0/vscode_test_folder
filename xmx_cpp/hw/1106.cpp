//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=1106&isOOP=false最大公约数
#include <iostream>

using namespace std;

long long gcd(long long a,long long b){
    if(b==0) return a;
    return gcd(b,a%b);
}

int main(){
    long long a,b;
    cin >> a >> b;
    cout << gcd(a,b) << endl;
}