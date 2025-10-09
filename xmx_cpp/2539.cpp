#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>
#include <locale> // 修正 (1)：为 std::locale 添加了必需的头文件

// --- 以下代码与之前相同 ---

// 课程常量
const int YUWEN = 0;
const int SUANSHU = 1;
const int ZHENGZHI = 2;
const int DILI = 3;
const int YINYUE = 4;
const int MEISHU = 5;

// 老师常量
const int TEACHER_A = 0;
const int TEACHER_B = 1;
const int TEACHER_C = 2;

// 课程名称数组
const std::vector<std::string> subjects = {
    "语文", "算术", "政治", "地理", "音乐", "美术"
};

// 检查函数：判断一个课程分配方案是否满足所有条件
bool check(const std::vector<int>& p) {
    std::map<int, int> teacherOf;
    teacherOf[p[0]] = TEACHER_A;
    teacherOf[p[1]] = TEACHER_A;
    teacherOf[p[2]] = TEACHER_B;
    teacherOf[p[3]] = TEACHER_B;
    teacherOf[p[4]] = TEACHER_C;
    teacherOf[p[5]] = TEACHER_C;

    if (teacherOf.at(ZHENGZHI) == teacherOf.at(SUANSHU)) return false;
    if (teacherOf.at(DILI) == TEACHER_B) return false;
    if (teacherOf.at(DILI) == TEACHER_A || teacherOf.at(SUANSHU) == TEACHER_A) return false;
    if (teacherOf.at(YINYUE) == TEACHER_B || teacherOf.at(YUWEN) == TEACHER_B) return false;
    
    return true;
}

int main() {
    try {
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale(""));
    } catch(...) {

    }
    
    std::vector<int> p(6);
    std::iota(p.begin(), p.end(), 0);

    do {
        if (check(p)) {
  
            std::string a_subj1 = subjects[p[0]];
            std::string a_subj2 = subjects[p[1]];

            if (a_subj1 > a_subj2) std::swap(a_subj1, a_subj2);
            std::cout << a_subj1 << " " << a_subj2 << std::endl;
            
            std::string b_subj1 = subjects[p[2]];
            std::string b_subj2 = subjects[p[3]];
            if (b_subj1 > b_subj2) std::swap(b_subj1, b_subj2);
            std::cout << b_subj1 << " " << b_subj2 << std::endl;

            std::string c_subj1 = subjects[p[4]];
            std::string c_subj2 = subjects[p[5]];
            if (c_subj1 > c_subj2) std::swap(c_subj1, c_subj2);
            std::cout << c_subj1 << " " << c_subj2 << std::endl;

            break;
        }
    } while (std::next_permutation(p.begin(), p.end()));

    return 0;
}