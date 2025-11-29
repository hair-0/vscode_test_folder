# include <iostream>
using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int M,N,K;

	std::cin >> M >> N >> K;

	for (int i = M ; i < N; ++i)
	{
        	std:: cout << static_cast<char>(i);
		if ((i-M+1)%K == 0)
		{
			std::cout << std::endl;
		}
	}

	return 0;
}
