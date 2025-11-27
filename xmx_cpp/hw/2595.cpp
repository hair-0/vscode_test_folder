//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1383&pid=2595&isOOP=false
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<int> A, B, C;

void print_vector(const vector<int>& vec) {
    if (vec.empty()) {
        std::cout << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << endl;
}

void print_state() {
    print_vector(A);
    print_vector(B);
    print_vector(C);
}

bool perform_move(char src_char, char dest_char, map<char, vector<int>*>& vec_map) {
    vector<int>* src_vec = vec_map[src_char];
    vector<int>* dest_vec = vec_map[dest_char];

    if (src_vec->empty()) {
        return false;
    }

    int moved_num = src_vec->back();

    if (!dest_vec->empty()) {
        int dest_top_num = dest_vec->back();
        if (moved_num > dest_top_num) {
            return false;
        }
    }

    src_vec->pop_back(); 
    dest_vec->push_back(moved_num);

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;

    A.resize(N);
    for (int i = 0; i < N; ++i) {
        if (!(std::cin >> A[i])) return 0;
    }
    
    int M;
    if (!(std::cin >> M)) return 0;

    map<char, vector<int>*> vec_map = {
        {'A', &A},
        {'B', &B},
        {'C', &C}
    };

    print_state();

    for (int i = 0; i < M; ++i) {
        string action_str;
        if (!(std::cin >> action_str)) break;

        char src_char = action_str[0];
        char dest_char = action_str[1];

        if (!perform_move(src_char, dest_char, vec_map)) {
            std::cout << "ERROR" << endl;
            return 0; 
        }

        print_state();

        if (A.empty() && B.empty()) {
            return 0; 
        }
    }

    return 0;
}