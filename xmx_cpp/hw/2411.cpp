#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
    string text;
    getline(cin, text);

    string result = "";
    string word = "";

    for (int i = 0; i < text.length();i++){
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c<= 'Z')){
            word += c;
        }
        else{
            if (!word.empty()){
                reverse(word.begin(), word.end());
                result += word;
                word = "";
            }
            result += c;
        }
    }

    if (!word.empty()){
        reverse(word.begin(),word.end());
        result += word;
    }

    cout << result << endl;

    return 0;
}