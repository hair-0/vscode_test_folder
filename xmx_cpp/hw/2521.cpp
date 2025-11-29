#include <iostream>
using namespace std;

int main() {
    for (int rank_a = 1; rank_a <= 5; ++rank_a) {
        for (int rank_b = 1; rank_b <= 5; ++rank_b) {
            for (int rank_c = 1; rank_c <= 5; ++rank_c) {
                for (int rank_d = 1; rank_d <= 5; ++rank_d) {
                    for (int rank_e = 1; rank_e <= 5; ++rank_e) {
                        
                        if (rank_a == rank_b || rank_a == rank_c || rank_a == rank_d || rank_a == rank_e ||
                            rank_b == rank_c || rank_b == rank_d || rank_b == rank_e ||
                            rank_c == rank_d || rank_c == rank_e ||
                            rank_d == rank_e) {
                            continue;
                        }

                        if (rank_e == 2 || rank_e == 3) {
                            continue;
                        }

                        bool guess_A_is_true = (rank_e == 1);
                        bool guess_B_is_true = (rank_b == 2);
                        bool guess_C_is_true = (rank_a == 5);
                        bool guess_D_is_true = (rank_c != 1);
                        bool guess_E_is_true = (rank_d == 1);

                        bool condition_met = true;

                        if (rank_a == 1 && !guess_A_is_true) condition_met = false;
                        if (rank_b == 1 && !guess_B_is_true) condition_met = false;
                        if (rank_c == 1 && !guess_C_is_true) condition_met = false;
                        if (rank_d == 1 && !guess_D_is_true) condition_met = false;
                        if (rank_e == 1 && !guess_E_is_true) condition_met = false;
                        
                        if (rank_a == 2 && !guess_A_is_true) condition_met = false;
                        if (rank_b == 2 && !guess_B_is_true) condition_met = false;
                        if (rank_c == 2 && !guess_C_is_true) condition_met = false;
                        if (rank_d == 2 && !guess_D_is_true) condition_met = false;
                        if (rank_e == 2 && !guess_E_is_true) condition_met = false;

                        if (rank_a == 3 && guess_A_is_true) condition_met = false;
                        if (rank_b == 3 && guess_B_is_true) condition_met = false;
                        if (rank_c == 3 && guess_C_is_true) condition_met = false;
                        if (rank_d == 3 && guess_D_is_true) condition_met = false;
                        if (rank_e == 3 && guess_E_is_true) condition_met = false;
                        
                        if (rank_a == 4 && guess_A_is_true) condition_met = false;
                        if (rank_b == 4 && guess_B_is_true) condition_met = false;
                        if (rank_c == 4 && guess_C_is_true) condition_met = false;
                        if (rank_d == 4 && guess_D_is_true) condition_met = false;
                        if (rank_e == 4 && guess_E_is_true) condition_met = false;

                        if (rank_a == 5 && guess_A_is_true) condition_met = false;
                        if (rank_b == 5 && guess_B_is_true) condition_met = false;
                        if (rank_c == 5 && guess_C_is_true) condition_met = false;
                        if (rank_d == 5 && guess_D_is_true) condition_met = false;
                        if (rank_e == 5 && guess_E_is_true) condition_met = false;
                        
                        if (condition_met) {
                            std::cout << rank_a << " " << rank_b << " " << rank_c << " " << rank_d << " " << rank_e << std::endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 0;
}