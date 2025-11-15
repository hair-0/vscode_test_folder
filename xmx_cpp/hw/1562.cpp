# include <iostream>
using namespace std;

bool checkSpecial(int i, int n);

bool checkSpecial(int i, int n)
{
	int origin_num = i;
	int sum = 0;
	int reversed_num = 0;

	while (i > 0)
	{
		int digit = i % 10;
		sum += digit;
		reversed_num = reversed_num*10 + digit;
		i /= 10;
	}

	if (sum == n && origin_num == reversed_num)
	{
		return true;
	
	}
	return false;

}

int main()
{
	int n;
	cin >> n;
	for (int i = 10000; i < 1000000; i++)
	{
		if (checkSpecial(i,n))
		{
			cout << i << endl;
		}

	}

	return 0;

}

