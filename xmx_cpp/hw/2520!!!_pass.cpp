//使用新学习的动态数组vector来完成排序
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
	std::vector<int> InputNumber(4);
	for (int& num : InputNumber){
		cin >> num;
	}
	std::sort(InputNumber.begin(), InputNumber.end());

	for (int i = 0; i < InputNumber.size(); ++i){
		std::cout << InputNumber[i];
		if (i < InputNumber.size() - 1){
			std::cout << ' ' ;
		}
		
	}

	return 0;
}
/*后半段也可使用‘ : ’来遍历
	// 使用 is_first 技巧控制空格
	bool is_first = true; 
    
    // 注意：这里使用 int number 而不是 int& number，因为我们只是读取/输出，不需要修改
    for (int number : InputNumber) { 
        
        // 核心逻辑：如果是第二个、第三个、第四个元素...
        if (!is_first) {
            cout << " "; // 先输出一个空格
        }
			//将空格前缀，不用担心最后一个输出数字的后面出现空格
        
        cout << number; // 输出当前数字
        
        // 标记：第一个元素已经处理完毕
        is_first = false; 
    }
    
    // 5. 输出最后的换行符
    cout << endl;

    return 0;
}

*/




/*oj上提交的代码：逐个比较法，符合oj的要求
# include <iostream>
# include <iomanip>

using namespace std;


int main(){

	int a,b,c,d=0;
	int temp=0;
	std::cin>>a>>b>>c>>d;

	if (a-b>0){
		temp=a;
		a=b;
		b=temp;
	}
	else{

	}

	if (a-c>0){
			temp=a;
			a=c;
			c=temp;
	}
	else{

	}

	if (a-d>0){
		temp=a;
		a=d;
		d=temp;
	}
	else{

	}

	if (b-c>0){
		temp=b;
		b=c;
		c=temp;
	}
	else{

	}

	if (b-d>0){
		temp=b;
		b=d;
		d=temp;
	}
	else{

	}

	if (c-d>0){
		temp=c;
		c=d;
		d=temp;
	}
	else{

	}

	std::cout << a << ' ' << b << ' ' << c << ' ' << d  << endl;

	return 0;

}
*/
