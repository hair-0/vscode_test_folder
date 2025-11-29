# include <iostream>
# include <cmath>
using namespace std;

double delta(double a,double b,double c)
{
    double judge = b*b - 4.0*a*c;
    return judge;
}

int root_num(double a,double b, double c)
{
    if (a==0)
    {
        if (b==0 && c==0)
        {
            return -1;
        }
        if (b==0 && c!=0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    double judge = b*b - 4.0*a*c;
    if (a!=0)
    {
        if (judge==0.0)
            return 1;
        if (judge>0.0)
            return 2;
        if (judge<0.0)
            return 0; 
    }
    return 0;
}

int main()
{
    double a,b,c;
    cin >> a >> b >> c;
    cout << root_num(a,b,c);
    return 0;
}