# include <iostream>
using namespace std;


int main()
{
	int num;

	int count=0,sum=0;
	
	cin>>num;
	if (num==0)
	{
		cout << "0 0" << endl;
		return 0;
	}
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}
   
	cin >> num;
	if (num==0)
	{
		cout << count << " " << sum << endl;
		return 0;
	} 
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}

	cin>>num;
	if (num==0)
	{
		cout << count << " " << sum << endl;
		return 0;
	}
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}

	cin>>num;
	if (num==0)
	{
		cout << count << " " << sum << endl;
		return 0;
	}
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}

	cin>>num;

	if (num==0)
	{
		cout << count << " " << sum << endl;
		return 0;
	}
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}


	cin>>num;

	if (num==0)
	{
		cout << count << " " << sum << endl;
		return 0;
	}
	if (num%2!=0 && num%3!=0 && num%5!=0 && num%7!=0)
	{	count++;
		sum += num;

	}

	return 0;
}
