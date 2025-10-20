# include <iostream>
using namespace std;

int main() {
    for (char killer = 'A'; killer <= 'F'; ++killer) {
        int truth[6] = {0};
	
	    //A truth
        if (killer != 'A') {
            truth[0] = 1;
        }
        //B truth
        if (killer == 'A' || killer == 'C') {
            truth[1] = 1;
        }

        
        if (truth[0] == 0 && truth[1] == 0) {
            truth[2] = 1;
        }

        
        if (killer == 'F') {
            truth[5] = 1; 
        }

        
        if (truth[2] == 0 && truth[5] == 0) {
            truth[3] = 1;
        }

        if (truth[0] == 1 && truth[3] == 1 && truth[1] == 0 && truth[2] == 0 && truth[5] == 0) {
            truth[4] = 1;
        }


        int truth_count = 0;
        for (int i = 0; i < 6; ++i) {
            if (truth[i] == 1) {
                truth_count++;
            }
        }

        if (truth_count == 3) {
            std::cout << killer << std::endl;
        }
    }

    return 0;
}   