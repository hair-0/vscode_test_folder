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
