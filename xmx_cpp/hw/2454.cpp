//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1389&pid=2454&isOOP=false
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Tank {
    string name;
    int power;
    int defense;
};

bool compareTanks(const Tank& a, const Tank& b) {
    if (a.power != b.power) {
        return a.power < b.power;
    }
    if (a.defense != b.defense) {
        return a.defense < b.defense;
    }
    return a.name < b.name;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<Tank> tanks;

    while (n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "ADD") {
            string name;
            int p, d;
            cin >> name >> p >> d;
            tanks.push_back({name, p, d});
        } 
        else if (cmd == "SELECT") {
            string name;
            cin >> name;
            for (auto it = tanks.begin(); it != tanks.end(); ++it) {
                if (it->name == name) {
                    Tank temp = *it;
                    tanks.erase(it);
                    tanks.insert(tanks.begin(), temp);
                    break;
                }
            }
        } 
        else if (cmd == "LEAVE") {
            string name;
            cin >> name;
            for (auto it = tanks.begin(); it != tanks.end(); ++it) {
                if (it->name == name) {
                    tanks.erase(it);
                    break;
                }
            }
        } 
        else if (cmd == "PROMOTE") {
            string name;
            int p, d;
            cin >> name >> p >> d;
            for (auto it = tanks.begin(); it != tanks.end(); ++it) {
                if (it->name == name) {
                    it->power = p;
                    it->defense = d;
                    break;
                }
            }
        } 
        else if (cmd == "ORDER") {
            sort(tanks.begin(), tanks.end(), compareTanks);
        }
    }

    for (const auto& t : tanks) {
        cout << t.name << " " << t.power << " " << t.defense << endl;
    }

    return 0;
}