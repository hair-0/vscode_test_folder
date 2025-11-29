#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {

    string lakes[4] = {"洞庭湖", "洪泽湖", "鄱阳湖", "太湖"};
    int order[4] = {0, 1, 2, 3};
    
    do {
       
        int countA = 0;
        if (order[0] == 0) countA++;
        if (order[3] == 1) countA++; 
        if (order[2] == 2) countA++; 
        
        
        int countB = 0;
        if (order[0] == 1) countB++; 
        if (order[3] == 0) countB++; 
        if (order[1] == 2) countB++; 
        if (order[2] == 3) countB++; 
        
        
        int countC = 0;
        if (order[3] == 1) countC++; 
        if (order[2] == 0) countC++; 
        
        
        int countD = 0;
        if (order[0] == 2) countD++; 
        if (order[3] == 3) countD++; 
        if (order[1] == 1) countD++; 
        if (order[2] == 0) countD++; 
        
        
        if (countA == 1 && countB == 1 && countC == 1 && countD == 1) {
            for (int i = 0; i < 4; i++) {
                cout << lakes[order[i]];
                if (i < 3) cout << " ";
            }
            cout << endl;
            break;
        }
    } while (next_permutation(order, order + 4));
    
    return 0;
}
