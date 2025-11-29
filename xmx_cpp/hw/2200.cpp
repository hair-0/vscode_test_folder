//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=2200&isOOP=false
# include <iostream>
using namespace std;

int f1_value;
int f(int x){
    if (x <= 0) return 0;
    if (x == 1) return f1_value;
    else return f(x-1)+f(x/2)+f(x/3);
}

int main(){
    int n;
    std::cin >> f1_value >> n;
    if (f1_value <= 20 && f1_value > 0 && n > 0 && n <= 20){
        std::cout << f(n) << endl;
        return 0;
    }
    return 0;
}