#include <iostream>  // 引入输入输出流库，用于 std::cout
using namespace std;

int main() {
    int arr[5] = {300,350,150,400,200};
    int max = 0;
    for(int i = 0 ;i < 5 ;i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    cout << max << endl;
    system("pause");  // ✅ 等待按键，防止程序运行后窗口立即关闭
    
    return 0;  // 返回 0 表示程序正常结束
}