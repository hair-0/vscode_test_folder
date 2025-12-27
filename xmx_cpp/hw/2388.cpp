//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1396&pid=2388&isOOP=false
//考察数据结构的构建(菜单树)和状态机的模拟(用户在菜单间的跳转)

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>

using namespace std;

struct Menu {
    string name;
    vector<Menu> subs;
};

vector<Menu> root;
Menu* current_lvl1 = nullptr;

void print_menu() {
    vector<Menu>* list;
    if (current_lvl1 == nullptr) {
        list = &root;
    } else {
        list = &(current_lvl1->subs);
    }

    for (int i = 0; i < list->size(); ++i) {
        cout << "[" << (i + 1) << "] " << (*list)[i].name << endl;
    }
    if (current_lvl1 != nullptr) {
        cout << "[#] BACK" << endl;
    }
}

int main() {
    freopen("config.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    string line;
    getline(cin, line); 

    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        if (line.empty()) { i--; continue; }
        
        int start = line.find_first_not_of("# ");
        string name = line.substr(start);

        if (line.substr(0, 2) == "##") {
            root.back().subs.push_back({name, {}});
        } else {
            root.push_back({name, {}});
        }
    }

    string s;
    cin >> s;

    print_menu();

    for (char op : s) {
        cout << endl;

        if (op == '#') {
            if (current_lvl1 != nullptr) {
                current_lvl1 = nullptr;
                print_menu();
            } else {
                cout << "Invalid input!" << endl;
                print_menu();
            }
        } else if (isdigit(op)) {
            int idx = op - '1';
            vector<Menu>* list = (current_lvl1 == nullptr) ? &root : &(current_lvl1->subs);

            if (idx >= 0 && idx < list->size()) {
                Menu* target = &(*list)[idx];
                
                if (target->subs.empty()) {
                    string path;
                    if (current_lvl1 == nullptr) path = "<" + target->name + ">";
                    else path = "<" + current_lvl1->name + "/" + target->name + ">";
                    
                    cout << "Running " << path << endl;
                    print_menu();
                } else {
                    current_lvl1 = target;
                    print_menu();
                }
            } else {
                cout << "Invalid input!" << endl;
                print_menu();
            }
        } else {
            cout << "Invalid input!" << endl;
            print_menu();
        }
    }

    return 0;
}