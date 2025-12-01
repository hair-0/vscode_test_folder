#include<iostream>

using namespace std;

void is_ryear(int x){
	if (x % 4 == 0 && x % 400 == 0){
		cout << "YES" << endl;
	}
	else if (x % 4 ==0 && x % 100 ==0){
		cout << "NO" << endl;
	}
	else if (x % 4 ==0){
		cout << "YES" << endl;
	}
	else{
		cout << "NO" << endl;
	}
	return ;
}

int main(){
	int a;
	cin >> a;

	is_ryear(a);

	return 0;
}
/*
# include <iostream>
using namespace std;

int main(){

	int year = 0 ;
	std::cin >> year;

	if (year%400==0){
		std::cout<<"YES"<<std::endl;
	}

	else if (year%100==0){
		std::cout<<"NO"<<std::endl;
	}

	else if (year%4==0){
		std::cout<<"YES"<<std::endl;
	}

	else {
		std::cout<<"NO"<<std::endl;
	}

	return 0 ;
}
*/