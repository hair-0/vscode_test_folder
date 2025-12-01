# include <iostream>
# include <iomanip>

using namespace std;

int main(){
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
	double sum = 0.0;
	int number = 0;	
	std::cin >> a >> b >> c >> d >> e >> f;

	/* 
	1. 读取输入
    注意：根据题目要求，我们可以假设输入是合法的，不需要进行边界检查 (0 <= x <= 1000)
    除非这是一个严格要求错误处理的系统。在竞争性编程中，通常省略输入的边界检查。
	if (a >= 0 && a <= 1000 &&
		b >= 0 && b <= 1000 &&
		c >= 0 && c <= 1000 &&
		d >= 0 && d <= 1000 &&
		e >= 0 && e <= 1000 &&
		f >= 0 && f <= 1000)
	{

	}
	*/
		if (a%2==1 && a%3==0){
			sum+=a;
			number+=1;
		}
		else{

		}

		if (b%2==1 && b%3==0){
			sum+=b;
			number+=1;
		}
		else{
	
		}


		if (c%2==1 && c%3==0){
			sum+=c;
			number+=1;
		}
		else{

		}

		if (d%2==1 && d%3==0){
			sum+=d;
			number+=1;
		}
		else{
	
		}

		if (e%2==1 && e%3==0){
			sum+=e;
			number+=1;
		}
		else{

		}

		if (f%2==1 && f%3==0){
			sum+=f;
			number+=1;
		}
		else{

		}

		if (number !=0) {
		double average=sum/number;
			cout << fixed << setprecision(4) << average << endl;
		}

		if (number ==0){
			cout << 0.0000 << endl;
		}	

		else{

		}
	
	return 0;
}


/* 方案2: 使用vector数组
#include <iostream>
#include <iomanip>
#include <vector> // 引入 vector 库

using namespace std;

int main() {
    // 定义常量 N = 6，表示要处理的数字个数
    const int N = 6; 
    // 定义一个存储整数的 vector，大小为 N (即 6 个)
    vector<int> numbers(N); 

    double sum = 0.0; // 初始化总和（使用 double 以便计算平均值）
    int count = 0;    // 初始化符合条件的数字个数

    // A. 循环读取输入
    for (int i = 0; i < N; ++i) {
        // 读取第 i 个数字并存入 vector 的第 i 个位置
        cin >> numbers[i]; 
    }

    // B. 循环处理数据
    // 这是一个增强的 for 循环 (C++11 引入)，更简洁
    // 对于 numbers 数组中的每一个元素，都临时命名为 num
    for (int num : numbers) { 
        
        // C. 核心判断
        if (num % 6 == 3) { 
            sum += num; // 如果满足条件，加到总和 sum 中
            count++;    // 符合条件的数字个数加 1
        }
    }

    // D. 输出结果
    // 设置输出格式：定点表示，保留 4 位小数
    cout << fixed << setprecision(4); 

    if (count > 0) { // 如果至少有一个数符合要求
        double average = sum / count; // 计算平均值
        cout << average << endl;
    } else { // 如果没有数符合要求
        cout << 0.0000 << endl; // 输出 0.0000
    }

    return 0;
}
*/

/*方案3：使用函数、循环和数组
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// A. 独立函数定义（在 main 函数之上）
// 作用：判断输入 n 是否符合“奇数且是3的倍数”的条件
bool isOddMultipleOfThree(int n) {
    return n % 6 == 3;
}

int main() {
    const int N = 6;
    vector<int> numbers(N);
    double sum = 0.0;
    int count = 0;

    // B. 循环读取输入（与方案 2 相同）
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }

    // C. 循环处理数据
    for (int num : numbers) {
        // D. 核心判断 - 调用函数
        // 这一行比方案 2 更清晰地表达了意图
        if (isOddMultipleOfThree(num)) { 
            sum += num;
            count++;
        }
    }

    // E. 输出结果（与方案 2 相同）
    cout << fixed << setprecision(4);
    if (count > 0) {
        cout << sum / count << endl;
    } else {
        cout << 0.0000 << endl;
    }

    return 0;
}
*/