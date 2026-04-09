#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int heads, feet;

    cout << "========== 鸡兔同笼问题 ==========" << endl;
    cout << "鸡: 2只脚, 兔子: 4只脚" << endl;
    cout << "==================================" << endl;

    cout << "请输入头的总数: ";
    cin >> heads;
    cout << "请输入脚的总数: ";
    cin >> feet;

    // 计算兔子数量
    double rabbits = (feet - 2.0 * heads) / 2.0;
    double chickens = heads - rabbits;

    // 验证结果
    if (rabbits < 0 || chickens < 0) {
        cout << "输入错误：计算结果为负数！" << endl;
    } else if (floor(rabbits) != rabbits || floor(chickens) != chickens) {
        cout << "输入错误：计算结果不是整数！" << endl;
    } else if (feet % 2 != 0) {
        cout << "输入错误：脚的总数必须是偶数！" << endl;
    } else {
        cout << "\n计算结果：" << endl;
        cout << "鸡: " << (int)chickens << " 只" << endl;
        cout << "兔子: " << (int)rabbits << " 只" << endl;
    }

    return 0;
}
