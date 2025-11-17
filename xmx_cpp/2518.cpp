#include<iostream>
#include<cmath>
using namespace std;

int main(){

int x=0;
int y=0;

cin >> x >> y ;

if (100<=x && x<=999 && 0<=y && y<=9){
	int z=0;
	z=(x/10)%10;
	if (z==y){
		cout << "YES" << endl;
        }
	else {
		cout << "NO" << endl;
	}
}
else{
	
	}

return 0;

}
