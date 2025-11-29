//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=1205&isOOP=false
#include <iostream>
using namespace std;

int f(int x){
    if (x==1) return 1;
    else if (x>1 && x%2!=0){
        return f((x-1)/2)+f((x+1)/2);
    }
    else {
        return f(x/2);
    }
    return 0 ;
}

int main(){
    int T,i,y;
    std::cin >> T;
    for (i=0;i<T;i++){
        std::cin >> y;
        std::cout << f(y) << endl;
    }
    return 0;
}