# include <iostream>
using namespace std;


int main(){
	int a,b,c,d,e;
	int ta,tb,tc,td,te;
	int posa,posb,posc,posd,pose;
	
	for (posa=1;posa<=5;posa++){
		for (posb=1;posb<=5;posb++){
			if (posa==posb) continue;
			for (posc=1;posc<=5;posc++){
				if (posc == posa || posc == posb) continue;
				for (posd=1;posd<=5;posd++){
				if (posd == posa || posd == posb || posd == posc ) continue;

				pose = 15-posa-posb-posc-posd;
 			
				ta = ((posb == 2) + (posa == 3));
				tb = ((posb == 2) + (pose == 4));
				tc = ((posc == 1) + (posd == 2));
				td = ((posc == 5) + (posd == 3));
				te = ((pose == 4) + (posa == 1));

				if (ta == 1 && tb ==1 && tc == 1 && td == 1 && te ==1){
					for (int i =1 ; i <=5; i++){
						if (posa == i) cout << 'A';
						else if (posb == i) cout << 'B';
						else if (posc == i) cout << 'C';
						else if (posd == i) cout << 'D';
						else cout << 'E';
			
						cout << (i<5? ' ': '\n');		
								            	}
											                            }

					                  	    }
				                      }

	                                }

								}


	return 0;
}
