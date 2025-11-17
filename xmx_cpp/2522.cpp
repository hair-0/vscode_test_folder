# include<iostream>
using namespace std;

//这道题我打算使用位运算来实现判断第pos位是否为1

bool is_one(int m,int pos)
{
	return (m >> pos) & 1; 
}


void print_bits(int m)
{
	for (int i = 31; i>=0; --i)
	{
		if (is_one(m,i))
		{
			cout << '1';

		}
		else
		{
			cout << '0';
		}
	}


}


int main()
{
	int n;
	cin >> n;
	print_bits(n);
	return 0;

}
