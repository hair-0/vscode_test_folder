#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main(){
    double a=1.0; 
    double b=-3.0; 
    double c=2.0;
    double delta=b*b-4*a*c;
    double x1=(-b+sqrt(delta))/(2*a);
    double x2=(-b-sqrt(delta))/(2*a);
    if (x1>x2){
        double temp=x1;
        x1=x2;
        x2=temp;
    }
    cout<<fixed<<setprecision(3)<<x1<<" "<<x2<<endl;

    a=2; b=-5; c=2;
    delta=b*b-4*a*c;
    x1=(-b+sqrt(delta))/(2*a);
    x2=(-b-sqrt(delta))/(2*a);
    if (x1>x2){
        double temp=x1;
        x1=x2;
        x2=temp;
    }
    cout<<fixed<<setprecision(3)<<x1<<" "<<x2<<endl;

    a=-3; b=10; c=2;
    delta=b*b-4*a*c;
    x1=(-b+sqrt(delta))/(2*a);
    x2=(-b-sqrt(delta))/(2*a);
    if (x1>x2){
        double temp=x1;
        x1=x2;
        x2=temp;
    }
    cout<<fixed<<setprecision(3)<<x1<<" "<<x2<<endl;

    return 0;







}