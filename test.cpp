#include <iostream>  // 引入输入输出流库，用于 std::cout
using namespace std;

int main() {
    cout << "这是一个C++示例程序：输出 1 到 1000 之间的斐波那契数列\n\n";

    // 斐波那契数列的前两个数
    int a = 1;  // 第一个数
    int b = 1;  // 第二个数

    cout << a << " " << b << " ";  // 先输出前两个数

    // 循环生成后续的数
    while (true) {
        int c = a + b;  // 新的数 = 前两个数的和

        if (c > 1000) {  // 如果超出 1000，结束循环
            break;
        }

        cout << c << " ";  // 输出当前数

        // 更新 a 和 b，准备下一轮
        a = b;
        b = c;
    }

    cout << "\n\n程序运行结束。\n";

    system("pause");  // ✅ 等待按键，防止程序运行后窗口立即关闭
    
    return 0;  // 返回 0 表示程序正常结束
}
