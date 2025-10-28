//By Claude-3.7-sonnet

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// ����γ̳���
const int YUWEN = 0;   // ���� YW
const int SUANSU = 1;  // ���� SS
const int ZHENGZHI = 2;// ���� ZZ
const int DILI = 3;    // ���� DL
const int YINYUE = 4;  // ���� YY
const int MEISHU = 5;  // ���� MS

bool isValid(vector<int> A, vector<int> B, vector<int> C) {
    vector<vector<int>> teachers = {A, B, C};
    
    // ���ÿ�ſ��Ƿ�ֻ��һ����ʦ����
    vector<bool> taught(6, false);
    for (const auto& courses : teachers) {
        for (int course : courses) {
            if (taught[course]) return false;
            taught[course] = true;
        }
    }
    
    // ������������ʦ��������ʦ���ھ�
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
    
    // �ҵ������ĺ͵������ʦ
    int chineseTeacher = -1, geoTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), YUWEN) != teachers[i].end()) {
            chineseTeacher = i;
        }
        if (find(teachers[i].begin(), teachers[i].end(), DILI) != teachers[i].end()) {
            geoTeacher = i;
        }
    }
    
    // ������ʦ��������ʦ�����
    // ���B��������ʦ�������ʦ����Ҫ���⴦����ΪB���������
    if (chineseTeacher == 1 && geoTeacher != 1) {
        // B��������ʦ����ô������ʦ���벻��B
    } else if (geoTeacher == 1) {
        // B�����ǵ�����ʦ����Ϊ������ʦ��������ʦ����󣬶�B���������
        return false;
    } else if (chineseTeacher == geoTeacher) {
        // ͬһ�˲���ͬʱ�����ĺ͵���
        return false;
    }
    
    // �ҵ�����������ʦ
    int artTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), MEISHU) != teachers[i].end()) {
            artTeacher = i;
            break;
        }
    }
    
    // A�����Ե�����ʦ��������ʦ������������ѧ��Ʒ
    // A����ͬʱ�ǵ�����ʦ��������ʦ
    if (geoTeacher == 0 || artTeacher == 0) {
        return false;
    }
    
    // �ҵ������ֵ���ʦ
    int musicTeacher = -1;
    for (int i = 0; i < 3; ++i) {
        if (find(teachers[i].begin(), teachers[i].end(), YINYUE) != teachers[i].end()) {
            musicTeacher = i;
            break;
        }
    }
    
    // B������������ʦ��������ʦһ����Ӿ
    // B����ͬʱ��������ʦ��������ʦ
    if (musicTeacher == 1 || chineseTeacher == 1) {
        return false;
    }
    
    return true;
}

string getCourseStr(int course) {
    switch (course) {
        case YUWEN: return "����";
        case SUANSU: return "����";
        case ZHENGZHI: return "����";
        case DILI: return "����";
        case YINYUE: return "����";
        case MEISHU: return "����";
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
    // ��ƴ������ĸ����
    sort(A.begin(), A.end(), compareByInitial);
    sort(B.begin(), B.end(), compareByInitial);
    sort(C.begin(), C.end(), compareByInitial);
    
    cout << "A " << getCourseStr(A[0]) << " " << getCourseStr(A[1]) << endl;
    cout << "B " << getCourseStr(B[0]) << " " << getCourseStr(B[1]) << endl;
    cout << "C " << getCourseStr(C[0]) << " " << getCourseStr(C[1]) << endl;
}

int main() {
    vector<int> courses = {YUWEN, SUANSU, ZHENGZHI, DILI, YINYUE, MEISHU};
    
    // �������п��ܵĿγ̷���
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
    
    cout << "�޽�" << endl;
    return 0;
}