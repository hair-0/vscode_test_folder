//By Claude-3.7-sonnet

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// 定义课程常量
const int YUWEN = 0;   // 语文 YW
const int SUANSU = 1;  // 算术 SS
const int ZHENGZHI = 2;// 政治 ZZ
const int DILI = 3;    // 地理 DL
const int YINYUE = 4;  // 音乐 YY
const int MEISHU = 5;  // 美术 MS

bool isValid(vector<int> A, vector<int> B, vector<int> C) {
    vector<vector<int>> teachers = {A, B, C};
    
    // 检查每门课是否只被一个老师教授
    vector<bool> taught(6, false);
    for (const auto& courses : teachers) {
        for (int course : courses) {
            if (taught[course]) return false;
            taught[course] = true;
        }
    }
    
    // 条件：政治老师和算术老师是邻居
    int politicsTeacher = -1, mathTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), ZHENGZHI) != teachers[i].end()) {
            politicsTeacher = i;
        }
        if (find(teachers[i].begin(), teachers[i].end(), SUANSU) != teachers[i].end()) {
            mathTeacher = i;
        }
    }
    if (abs(politicsTeacher - mathTeacher) != 1) return false;
    
    // 找到教语文和地理的老师
    int chineseTeacher = -1, geoTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), YUWEN) != teachers[i].end()) {
            chineseTeacher = i;
        }
        if (find(teachers[i].begin(), teachers[i].end(), DILI) != teachers[i].end()) {
            geoTeacher = i;
        }
    }
    
    // 地理老师比语文老师年龄大
    // 如果B是语文老师或地理老师，需要特殊处理，因为B是最年轻的
    if (chineseTeacher == 1 && geoTeacher != 1) {
        // B是语文老师，那么地理老师必须不是B
    } else if (geoTeacher == 1) {
        // B不能是地理老师，因为地理老师比语文老师年龄大，而B是最年轻的
        return false;
    } else if (chineseTeacher == geoTeacher) {
        // 同一人不能同时教语文和地理
        return false;
    }
    
    // 找到教美术的老师
    int artTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), MEISHU) != teachers[i].end()) {
            artTeacher = i;
            break;
        }
    }
    
    // A经常对地理老师和美术老师讲他看过的文学作品
    // A不能同时是地理老师和美术老师
    if (geoTeacher == 0 || artTeacher == 0) {
        return false;
    }
    
    // 找到教音乐的老师
    int musicTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), YINYUE) != teachers[i].end()) {
            musicTeacher = i;
            break;
        }
    }
    
    // B经常和音乐老师、语文老师一起游泳
    // B不能同时是音乐老师和语文老师
    if (musicTeacher == 1 || chineseTeacher == 1) {
        return false;
    }
    
    return true;
}

string getCourseStr(int course) {
    switch (course) {
        case YUWEN: return "语文";
        case SUANSU: return "算术";
        case ZHENGZHI: return "政治";
        case DILI: return "地理";
        case YINYUE: return "音乐";
        case MEISHU: return "美术";
        default: return "";
    }
}

string getInitial(int course) {
    switch (course) {
        case YUWEN: return "YW";
        case SUANSU: return "SS";
        case ZHENGZHI: return "ZZ";
        case DILI: return "DL";
        case YINYUE: return "YY";
        case MEISHU: return "MS";
        default: return "";
    }
}

bool compareByInitial(int a, int b) {
    return getInitial(a) < getInitial(b);
}

void printResult(vector<int> A, vector<int> B, vector<int> C) {
    // 按拼音首字母排序
    sort(A.begin(), A.end(), compareByInitial);
    sort(B.begin(), B.end(), compareByInitial);
    sort(C.begin(), C.end(), compareByInitial);
    
    cout << "A " << getCourseStr(A[0]) << " " << getCourseStr(A[1]) << endl;
    cout << "B " << getCourseStr(B[0]) << " " << getCourseStr(B[1]) << endl;
    cout << "C " << getCourseStr(C[0]) << " " << getCourseStr(C[1]) << endl;
}

int main() {
    vector<int> courses = {YUWEN, SUANSU, ZHENGZHI, DILI, YINYUE, MEISHU};
    
    // 尝试所有可能的课程分配
    for (int a1 = 0; a1 < 6; ++a1) {
        for (int a2 = a1 + 1; a2 < 6; ++a2) {
            vector<int> A = {courses[a1], courses[a2]};
            
            for (int b1 = 0; b1 < 6; ++b1) {
                if (b1 == a1 || b1 == a2) continue;
                
                for (int b2 = b1 + 1; b2 < 6; ++b2) {
                    if (b2 == a1 || b2 == a2) continue;
                    
                    vector<int> B = {courses[b1], courses[b2]};
                    vector<int> C;
                    
                    for (int i = 0; i < 6; ++i) {
                        if (i != a1 && i != a2 && i != b1 && i != b2) {
                            C.push_back(courses[i]);
                        }
                    }
                    
                    if (isValid(A, B, C)) {
                        printResult(A, B, C);
                        return 0;
                    }
                }
            }
        }
    }
    
    cout << "无解" << endl;
    return 0;
}