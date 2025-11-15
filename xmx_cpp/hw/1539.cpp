# include<iostream>
# include<string>
using namespace std;

int main(){
    string binary;
    cin >> binary;
    int decimal = 0;
    for (int i = 0; i < binary.length(); i++){
        decimal = decimal << 1;
        decimal += (binary[i] - '0');

    }

    cout << decimal << endl;

    return 0;
}