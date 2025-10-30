#include<iostream>
#include<cstring>
using namespace std;

void count_chars(const char a[],int *p_letter,int *p_digit, int *p_other){
    *p_letter = 0;
    *p_digit = 0;
    *p_other = 0;

    for (int i = 0; a[i] != '\0'; ++i){
        if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z')){
            (*p_letter)++;
        }
        else if (a[i] >= '0' && a[i] <= '9'){
            (*p_digit)++;
        }
        else{
            *(p_other)++;
        }
    } 
}

void process_chars(char a[]){
    for (int i = 0; a[i] !='\0'; ++i){
        if (a[i] >= 'a' && a[i] <= 'z'){
            a[i] = a[i] + ('A'-'a');
        }

        else if (a[i] >= 'A' && a[i] <= 'Z'){
    
        }
        else if (a[i] >= '0' && a[i]<='9'){
            a[i] = '#';
        }
        else if (!((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a'&& a[i] <= 'z'))){
            a[i] = '.';
        }
    }
}


int main(){
    char s[100];
    cin.getline(s,100);

    int letters = 0, digits = 0, others = 0;
    count_chars(s, &letters, &digits, &others);

    process_chars(s);
    cout << s << endl;

    cout << "Letters:" << letters
          << ", Digits:"<< digits
          << ", Others:"<< others;
    return 0;
}
//others有问题