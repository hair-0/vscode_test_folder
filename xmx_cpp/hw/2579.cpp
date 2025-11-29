#include <iostream>
using namespace std;
 
///我个人的思路是采用指针的指针来解决这道题
int** transposeMatrix(int** original, int M, int N) {
    int** transposed = new int*[N];
    for (int i = 0; i < N; ++i) {
        transposed[i] = new int[M];
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            transposed[j][i] = original[i][j];
        }
    }
    return transposed;
}
 
int main() {
    int M, N;
    cin >> M >> N;
 
    int** original;
    int** transposed;
    
    ///为原始矩阵动态分配内存
     original = new int* [M];
     for (int i = 0; i < M; ++i){
        original[i] = new int[N];
     }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> original[i][j];
        }
    }
 
    transposed = transposeMatrix(original, M, N);
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }
 

    ///释放动态内存的代码，是进阶的优化
    // 释放动态分配的原始矩阵
    for (int i = 0; i < M; i++) {
        delete[] original[i];
    }
    delete[] original;
 
    // 释放动态分配的转置矩阵
    for (int i = 0; i < N; i++) {
        delete[] transposed[i];
    }
    delete[] transposed;

    return 0;
}