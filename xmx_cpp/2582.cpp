#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

char* format_line(const char* str) {
    char result[101];
    int i = 0;
    int j = 0;

    while (str[i] != '\0' && isspace(str[i])) {
        i++;
    }

    bool is_new_word = true;
    while (str[i] != '\0') {
        if (isalpha(str[i])) {
            if (is_new_word) {
                result[j] = toupper(str[i]);
                is_new_word = false;
            } else {
                result[j] = tolower(str[i]);
            }
            j++;
        }
        else if (isspace(str[i])) {
            if (j > 0 && result[j-1] != ' ') {
                result[j] = ' ';
                j++;
            }
            is_new_word = true;
        }
        i++;
    }

    if (j > 0 && result[j-1] == ' ') {
        j--;
    }

    result[j] = '\0';

    char* final_str = new char[j+1];
    strcpy(final_str, result);
    return final_str;
}


int main() {
    char input_line[100];
    cin.getline(input_line, 100);

    char* result_str = format_line(input_line);

    cout << result_str << endl;

    delete[] result_str;
    return 0;
}