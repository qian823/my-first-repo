#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // 初始化随机数种子，使用当前时间确保每次运行结果不同
    srand(time(0));

    // 生成1-100的随机数
    int target = rand() % 100 + 1;

    int guess;
    int count = 0;

    cout << "========== 猜数字游戏 ==========" << endl;
    cout << "我已经想好了一个1到100之间的整数" << endl;
    cout << "请你来猜一猜！" << endl;
    cout << "===============================" << endl;

    while (true) {
        cout << "\n请输入你的猜测: ";
        cin >> guess;

        // 验证输入是否有效
        if (cin.fail() || guess < 1 || guess > 100) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "请输入1到100之间的有效整数！" << endl;
            continue;
        }

        count++;

        if (guess == target) {
            cout << "\n恭喜你！猜对了！" << endl;
            cout << "你总共猜了 " << count << " 次。" << endl;
            break;
        } else if (guess < target) {
            cout << "猜小了！再大一点！" << endl;
        } else {
            cout << "猜大了！再小一点！" << endl;
        }
    }

    cout << "\n游戏结束，谢谢游玩！" << endl;

    return 0;
}
