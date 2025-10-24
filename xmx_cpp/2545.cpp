# include <iostream>
# include <iomanip>
using namespace std;

void print_calenda(int days, int first_day, int week_start)
{
//先查合法性
	if (days < 28 || days > 31 || first_day < 1 || first_day > 7 || week_start < 1 || week_start > 7)
	{
		std::cout << "ERROR";
		return;
	}
	
//第一天之前的空位
	int padding = (first_day - week_start + 7) % 7;
	for (int i = 0; i < padding; ++i)
	{
			cout << "   ";//三个空格
	}
	
//所有日期
	int day_of_week_counter = padding;
	for (int current_day = 1; current_day <= days; ++current_day)
	{
		cout << setfill('0') << setw(2) << current_day;
		day_of_week_counter++;
		
		if (day_of_week_counter == 7)
		{
			cout << endl;
			day_of_week_counter = 0;
		}
		else if (current_day < days)
		{
			cout << " ";
		}
	}
}

int main()
{
	int days,first_day,week_start;
	cin >> days >> first_day >> week_start;
	print_calenda(days,first_day,week_start);

	return 0;
}

