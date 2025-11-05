/*
http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1377&pid=2581&isOOP=false
*/

#include <iostream>
#include <cstring>
using namespace std;
 
// 补充结构体类型定义
// 结构体包含两个成员，分别为空格个数和空格位置。
// 空格位置是一个指针，指针指向一个动态分配的数组，数组长度为空格个数，数组元素为空格位置。 
 
 
// 补充函数头和函数体，返回值为结构体类型
 
 
int main()
{
    char input_line[100];
    cin.getline(input_line, 100);
 
    SpaceInfo result = analyze_spaces(input_line);
 
    cout << result.space_count << endl;
    for (int i = 0; i < result.space_count; ++i)
        cout << result.space_positions[i] << " ";
 
    delete[] result.space_positions;
    return 0;
}
