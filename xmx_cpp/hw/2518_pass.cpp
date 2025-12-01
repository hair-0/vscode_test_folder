#include<iostream>
#include<cmath>

using namespace std;

int main(){
	int x = 0;
	int y = 0;
	cin >> x >> y ;

	if (100 <= x && x <= 999 && 0 <= y && y <= 9){
		int middle = 0;
		middle = (x / 10) % 10;
		if (middle == y){
			cout << "YES" << endl;
			}
		else {
			cout << "NO" << endl;
		}
	}
	else{
		return 1;
		}

	return 0;
}
