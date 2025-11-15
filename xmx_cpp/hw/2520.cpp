# include <iostream>
# include <iomanip>
using namespace std;


int main(){

int a,b,c,d=0;
int temp=0;
std::cin>>a>>b>>c>>d;

if (a-b>0){
	temp=a;
	a=b;
	b=temp;
}
else{

}

if (a-c>0){
          temp=a;
          a=c;
          c=temp;
}
else{

}

if (a-d>0){
	temp=a;
	a=d;
	d=temp;
}
else{

}

if (b-c>0){
	temp=b;
	b=c;
	c=temp;
}
else{

}

if (b-d>0){
	temp=b;
	b=d;
	d=temp;
}
else{

}

if (c-d>0){
	temp=c;
	c=d;
	d=temp;
}
else{

}

std::cout << a << ' ' << b << ' ' << c << ' ' << d  << endl;

return 0;

}
