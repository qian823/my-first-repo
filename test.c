#include <stdio.h>   // 标准输入输出头文件，提供 printf、scanf 等函数
#include <math.h>    // 数学库，提供 sqrt() 函数
#include <stdlib.h>  // 提供 system() 函数声明
int main() {
    printf("这是一个C语言示例程序：输出1到200之间的所有质数\n\n");

    // 外层循环：从 2 到 100，逐个判断每个数是否是质数
    for (int num = 2; num <= 100; num++) {
        int isPrime = 1;  // 假设当前数字是质数（1 表示真，0 表示假）

        // 内层循环：判断 num 是否能被 2 ~ sqrt(num) 之间的数整除
        // 如果能整除，说明不是质数
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                isPrime = 0;  // 标记为不是质数
                break;        // 提前退出循环，节省计算
            }
        }

        // 如果 isPrime 依然为 1，说明该数是质数
        if (isPrime) {
            printf("%d ", num);
        }
    }

    printf("\n\n程序运行结束。\n");

    system("pause");  // ✅ 等待按键，防止程序运行后窗口立即关闭
    
    return 0;  // 返回 0 表示程序正常结束
}
