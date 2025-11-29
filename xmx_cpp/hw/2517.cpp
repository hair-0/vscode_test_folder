# include <iostream>
# include <cmath>
using namespace std;

int main(){
	
	int N;
	std::cin>> N;
	int workload=0;

	for (int i=0;i<N;++i){
		int readnumber;
		std::cin >> readnumber;

		if (readnumber % 2 !=0){
			int before_work=readnumber;
			int after_work=(readnumber%3);
			workload += abs(before_work - after_work);
			std::cout<<(after_work);

		}

		if (readnumber % 2 ==0){
			std:: cout << readnumber;
		}
		
		if (i < N-1){		
			std::cout<< " ";

		} 

	}

	std::cout << endl;
	std::cout << workload;


return 0;
}
