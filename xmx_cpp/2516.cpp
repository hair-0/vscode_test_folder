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