//重写采用函数定义的写法，最简单
#include<iostream>
#include<iomanip>

using namespace std;

void CylinderCout(double R, double r, double h){
    const double pi = 3.141592653589793; //不要习惯性地写成const int, 这里是const double
    double S = 2 * pi * h * (R + r);
    double V = pi * h *(R * R - r * r);
    cout << fixed << setprecision(5) << S << ' ' << V << endl;
}

int main(){
    CylinderCout(5.0, 2.0, 10.0);
    CylinderCout(3.5, 2.5, 5.5);
    CylinderCout(0.1, 0.001, 11.1);

    return 0;
}
/*没有学循环和数组前的解答方式
#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    const double pi=3.141592653589793;
    double R=5.0;
    double r=2.0;
    double h=10.0;
    double S=2*pi*h*(R+r);
    double V=pi*h*(R*R-r*r);
    cout<<fixed<<setprecision(5)<<S<<' '<<V<<endl;

    R=3.5; 
    r=2.5; 
    h=5.5;
    S=2*pi*h*(R+r);
    V=pi*h*(R*R -r*r);
    cout<<fixed<<setprecision(5)<<S<<' '<<V<<endl;
    
    R=0.1; r=0.001; h=11.1;
    S=2*pi*h*(R+r);
    V=pi*h*(R*R -r*r);
    cout<<fixed<<setprecision(5)<<S<<' '<<V<<endl;

    return 0;
}
*/

