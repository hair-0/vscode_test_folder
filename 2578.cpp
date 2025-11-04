#include<iostream>
using namespace std;

int square(int x);
int div2 (int x);
int poly2(int x);

int* map(int (*func)(int), const int* arr, int size){
    int* result = new int [size];
    for (int i = 0; i < size; ++i){
        result[i] = func(arr[i]);
    }
    return result;
}

int square(int x){
    return x * x;
}

int div2(int x){
    return x / 2;
}

int poly2(int x){
    return 3 * x + 2 * x + 1;
}

int main(){
    int size;
    cin >> size;
    int arr[1000];
    for(int i = 0; i < size; i++) cin >> arr[i];

    int (*op[3])(int) = {square, div2, poly2};

    cout << "0: square; 1: div2; 2: poly2" << endl;
    for (int i = 0; i < 3; ++i){
        int * result = map(op[i], arr, size);
        for(int j = 0; j < size; ++j){
            cout << result[j] << " ";
        }
        cout << endl;
        delete[] result;
    }
    return 0;
}