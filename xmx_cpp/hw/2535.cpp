# include <iostream>
using namespace std;

int main(){
	int A,B,C;
	int ta,tb,tc;

// situation 1: A > B > C
	 A=3,B=2,C=1;
	 ta=0,tb=0,tc=0;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) &&
	(B>C && tb<tc || B<C && tb>tc)
	){
	std:: cout<< "A B C"<<endl;
	return 0;
	}

// situation 2: A > C > B
	 A=3,C=2,B=1;
	 ta=0,tb=0,tc=0;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) &&
	(B>C && tb<tc || B<C && tb>tc)
	){
	std:: cout << "A C B" <<endl;
	return 0;
	}
	
	
// situation 3: B > A > C
	 B=3,A=2,C=1;
	 ta=0,tb=0,tc=0;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) &&
	(B>C && tb<tc || B<C && tb>tc)
	){
	std:: cout << "B A C" <<endl;
	return 0;
	}

// situation 4: B > C > A 
	 B=3,C=2,A=1;
	 ta=0,tb=0,tc=0;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) &&
	(B>C && tb<tc || B<C && tb>tc)
	){
	std:: cout << "B C A" << endl;
	return 0;
	}

// situation 5: C > A > B
	 C=3,A=2,B=1;
	 ta=0,tb=0,tc=0;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) && 
	(B>C && tb<tc || B<C && tb>tc)
	){
	std:: cout<< "C A B" << endl;	
	return 0;
	}

// situation 6: C > B > A
	 C=3,B=2,A=1;
	 ta=0,tb=2,tc=1;
	if (B>A) ta++; if (C==A) ta++;
	if (A>B) tb++; if (A>C)  tb++;
	if (C>B) tc++; if (B>A)  tc++;
	if (
	(A<B && ta>tb || A>B && ta<tb) &&
	(A<C && ta>tc || A>C && ta<tc) &&
	(B>C && tb<tc || B<C && tb>tc)
	){
	std::cout << "C B A" << endl;
	return 0;
	}



return 0;
}

