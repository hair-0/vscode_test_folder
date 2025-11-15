 #include <iostream>
 using namespace std;
  
int main() {
       for (int best = 1; best <= 4; ++best) {
           bool A = (best == 2);
           bool B = (best == 4);
          bool C = (best != 3);
           bool D = (!B);
 
          if (A + B + C + D == 1) {
              cout << best << "\n" << (D ? 'D' : A ? 'A' : B ? 'B' : 'C') << endl;
              return 0;
          }
      }
      return 0;
  }
 	


