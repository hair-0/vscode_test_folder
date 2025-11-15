# include <iostream>
# include <cmath>
# include <algorithm>
# include <cstdio>
using namespace std;

void calc(int a, int b, int c, int d, int*max_val, int*min_val, double*avg)
{
	*max_val = max(a, max(b, max(c,d)));
	*min_val = min(a, min(b, min(c,d)));
	*avg = (a + b + c + d) / 4.0;
}

int main()
{
	int a,b,c,d,max,min;
	double avg;
	std::cin >> a >> b >> c >> d;

	calc(a,b,c,d,&max,&min,&avg);

	printf("%d %d %6.4f",max,min,avg);
	return 0;

}
