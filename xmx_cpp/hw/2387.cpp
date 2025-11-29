//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1386&pid=2387&isOOP=false
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int N;
    cin >> N;
    char grid[25][25];
    int x,y;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> grid[i][j];
            if (grid[i][j] == 'H'){
                x = i;
                y = j;
            }
        }
    }

    string commands;
    cin >> commands;

    for (int k = 0; k < commands.length(); k++){
        char cmd = commands[k];
        int nx = x;
        int ny = y;

        if (cmd == 'w'){
            nx = x - 1;
        } else if (cmd == 's'){
            nx = x + 1;
        } else if (cmd == 'a'){
            ny = y - 1;
        } else if (cmd == 'd'){
            ny = y + 1;
        }

        if (nx >= 0 && nx < N && ny >= 0 && ny < N){
            grid[x][y] = '_';
            x = nx;
            y = ny;
            grid[x][y] = 'H';
        }
    

        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cout << grid[i][j];
                if (j < N - 1) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}