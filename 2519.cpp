# include <iostream>
# include <iomanip>
using namespace std;

int main(){

int a=0,b=0,c=0,d=0,e=0,f=0;
double sum=0;
int number=0;

std::cin>>a>>b>>c>>d>>e>>f;

if (a >= 0 && a <= 1000 &&
    b >= 0 && b <= 1000 &&
    c >= 0 && c <= 1000 &&
    d >= 0 && d <= 1000 &&
    e >= 0 && e <= 1000 &&
    f >= 0 && f <= 1000)
{

if (a%2==1 && a%3==0){
	 sum+=a;
	 number+=1;
}
else{

}

if (b%2==1 && b%3==0){
     sum+=b;
	 number+=1;
}
else{
 
}


if (c%2==1 && c%3==0){
	 sum+=c;
	 number+=1;
}
else{

}

if (d%2==1 && d%3==0){
     sum+=d;
	 number+=1;
}
else{
 
}

if (e%2==1 && e%3==0){
	 sum+=e;
	 number+=1;
}
else{

}

if (f%2==1 && f%3==0){
	 sum+=f;
	 number+=1;
}
else{

}

if (number !=0) {
double average=sum/number;
		cout<<fixed<<setprecision(4)<<average<<endl;
}

if (number ==0){
	cout<<fixed<<setprecision(4)<<0.0000<<std::endl;
}

else{


}

return 0;

}

}



