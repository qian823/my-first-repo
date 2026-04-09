#include <iostream>  // 引入输入输出流库，用于 std::cout
using namespace std;

int main() {
    for(int i = 1;i < 10;i++){
        for(int j = 1;j <= i;j++){
            cout << j << "*" << i << "=" <<j*i<<" ";
        }
        cout << endl;
    }

    system("pause");  // ✅ 等待按键，防止程序运行后窗口立即关闭
    
    return 0;  // 返回 0 表示程序正常结束
}