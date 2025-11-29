#include <iostream>
#include <string>
using namespace std;

int main() {
    string events[5] = {"百米", "四百米", "跳高", "跳远", "三级跳"};
    
    for (int a = 0; a < 5; a++) {
        for (int b = 0; b < 5; b++) {
            if (b == a) continue;
            for (int c = 0; c < 5; c++) {
                if (c == a || c == b) continue;
                for (int d = 0; d < 5; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = 0; e < 5; e++) {
                        if (e == a || e == b || e == c || e == d) continue;
                        
                        bool jia1 = (b == 4); 
                        bool jia2 = (d == 2);
                        if ((jia1 && jia2) || (!jia1 && !jia2)) continue;
                        
                         
                        bool yi1 = (a == 0); 
                        bool yi2 = (e == 2);
                        if ((yi1 && yi2) || (!yi1 && !yi2)) continue;
                        
                        
                        bool bing1 = (c == 3); 
                        bool bing2 = (d == 1); 
                        if ((bing1 && bing2) || (!bing1 && !bing2)) continue;
                        
                        
                        bool ding1 = (b == 2); 
                        bool ding2 = (e == 4);
                        if ((ding1 && ding2) || (!ding1 && !ding2)) continue;
                        
                       
                        cout << events[a] << " " << events[b] << " " 
                             << events[c] << " " << events[d] << " " 
                             << events[e] << endl;
                        return 0;
                    }
                }
            }
        }
    }
    
    return 0;
}
