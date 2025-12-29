//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1400&pid=2368&isOOP=false

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 定义字典
string nums_dict[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen"
};

// 转小写辅助函数（用于匹配）
string to_lower_case(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

int main() {
    // 关闭同步流加速IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> results;

    for (int k = 0; k < n; k++) {
        string word;
        cin >> word;
        
        // 复制一份转小写用于匹配字典
        string lower_word = to_lower_case(word);
        
        bool is_valid = false;
        for (int i = 0; i < 16; i++) {
            if (lower_word == nums_dict[i]) {
                is_valid = true;
                break;
            }
        }

        if (is_valid) {
            // 计算原始单词(保留原有大小写)的ASCII和
            int ascii_sum = 0;
            for (int i = 0; i < word.length(); i++) {
                ascii_sum += (int)word[i];
            }
            results.push_back(ascii_sum % 100);
        }
    }

    // 如果没有找到任何数字单词，根据题目要求，拼接数为 "0"
    // 经过后续去零规则（全0保留1个0），最终输出 0
    if (results.empty()) {
        cout << "0" << endl;
        return 0;
    }

    // 排序
    sort(results.begin(), results.end());

    // 拼接
    string final_str = "";
    for (int i = 0; i < results.size(); i++) {
        int val = results[i];
        // 如果小于10，前补0
        if (val < 10) {
            final_str += "0";
        }
        final_str += to_string(val);
    }

    // 去除前导零
    // 寻找第一个不为 '0' 的字符位置
    int start_idx = -1;
    for (int i = 0; i < final_str.length(); i++) {
        if (final_str[i] != '0') {
            start_idx = i;
            break;
        }
    }

    if (start_idx == -1) {
        // 如果没找到不为0的字符（说明全都是0），保留一个0
        cout << "0" << endl;
    } else {
        // 从第一个非0字符开始输出
        cout << final_str.substr(start_idx) << endl;
    }

    return 0;
}