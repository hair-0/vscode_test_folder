# include <iostream>
# include <iomanip>
using namespace std;

void print_calenda(int days, int first_day, int week_start)
{

//先查合法性
	if (days < 28 || days > 31)
	{
		std::cout << "ERROR" << std::endl;
		return;
	}
	if (first_day < 1 || first_day > 7)
	{
		std::cout << "ERROR" << std::endl;
		return;
	}

//再计算空位
	int first_day_0 = first_day - 1;
	int week_start_0 = week_start - 1;
	int offset = (first_day_0 - week_start_0 + 7) % 7;
	int day_grid = 0;
	
	for (int i=0; i < offset; ++i)
	{
	std::cout << std::setw(2) << " " << " ";
	day_grid ++;
	}
	
//print
	int current_day = 1;
	
	while (current_day <= days)
	{
		std::cout << std::setfill('0')<<std::setw(2) << current_day;
	day_grid ++;

		if (day_grid % 7 == 0)
		{
			std::cout << std::endl;
		}
		else
		{
			if (current_day < days)
			{
				std::cout << " ";
			}

		}
		current_day ++;

	}

	if (day_grid > 0 && day_grid % 7 !=0)
	{
		std::cout << std::endl;

	}

}


int main()
{
	int days,first_day,week_start;
	cin >> days >> first_day >> week_start;
	print_calenda(days,first_day,week_start);

	return 0;
}

