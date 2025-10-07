#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    
    vector<string> courses = {"语文", "算术", "政治", "地理", "音乐", "美术"};  
    vector<int> assignment = {0, 0, 1, 1, 2, 2}; 
    
    do {
        vector<string> A_courses, B_courses, C_courses;
        for (int i = 0; i < 6; i++) {
            if (assignment[i] == 0) A_courses.push_back(courses[i]);
            else if (assignment[i] == 1) B_courses.push_back(courses[i]);
            else C_courses.push_back(courses[i]);
        }
        
       
        bool condition1 = true;
        for (auto& course : A_courses) {
            if (course == "政治") {
                for (auto& c : A_courses) {
                    if (c == "算术") condition1 = false;
                }
            }
        }
        for (auto& course : B_courses) {
            if (course == "政治") {
                for (auto& c : B_courses) {
                    if (c == "算术") condition1 = false;
                }
            }
        }
        for (auto& course : C_courses) {
            if (course == "政治") {
                for (auto& c : C_courses) {
                    if (c == "算术") condition1 = false;
                }
            }
        }
        if (!condition1) continue;
        
        
        bool condition2 = true;
        
        for (auto& courses_list : {A_courses, B_courses, C_courses}) {
            bool has_geo = false, has_chi = false;
            for (auto& c : courses_list) {
                if (c == "地理") has_geo = true;
                if (c == "语文") has_chi = true;
            }
            if (has_geo && has_chi) {
                condition2 = false;
                break;
            }
        }
        if (!condition2) continue;
        
       
        bool condition4 = true;
        for (auto& course : A_courses) {
            if (course == "地理" || course == "算术") {
                condition4 = false;
                break;
            }
        }
        if (!condition4) continue;
      
        bool condition5 = true;
        for (auto& course : B_courses) {
            if (course == "音乐" || course == "语文") {
                condition5 = false;
                break;
            }
        }
        if (!condition5) continue;
        
       
        bool geo_teacher_B = false;
        for (auto& course : B_courses) {
            if (course == "地理") {
                geo_teacher_B = true;
                break;
            }
        }
        if (geo_teacher_B) continue; 
      
        sort(A_courses.begin(), A_courses.end());
        sort(B_courses.begin(), B_courses.end());
        sort(C_courses.begin(), C_courses.end());
        
        for (auto& course : A_courses) {
            cout << course << " ";
        }
        cout << endl;
        
        for (auto& course : B_courses) {
            cout << course << " ";
        }
        cout << endl;
        
        for (auto& course : C_courses) {
            cout << course << " ";
        }
        cout << endl;
        
        break;
        
    } while (next_permutation(assignment.begin(), assignment.end()));
    
    return 0;
}
