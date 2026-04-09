#include <iostream>
#include <string>
using namespace std;

// 判断是否需要敲桌子
bool shouldKnockTable(const string& numStr) {
    // 检查是否是7的倍数
    long long num = stoll(numStr);
    if (num % 7 == 0) {
        return true;
    }

    // 检查是否包含数字7
    for (char c : numStr) {
        if (c == '7') {
            return true;
        }
    }

    return false;
}

int main() {
    cout << "========== 敲桌子游戏 ==========" << endl;
    cout << "规则: 输入的数字是7的倍数或包含数字7时，需要敲桌子！" << endl;
    cout << "================================" << endl << endl;

    while (true) {
        string numStr;
        cout << "请输入一个数字 (输入 q 退出): ";
        cin >> numStr;

        if (numStr == "q" || numStr == "Q") {
            break;
        }

        // 检查输入是否为有效的数字
        bool isValid = true;
        for (char c : numStr) {
            if (c < '0' || c > '9') {
                isValid = false;
                break;
            }
        }

        if (!isValid) {
            cout << "输入无效，请输入一个正整数！" << endl << endl;
            continue;
        }

        if (shouldKnockTable(numStr)) {
            cout << "敲桌子！" << endl;
        } else {
            cout << "不用敲" << endl;
        }
        cout << endl;
    }

    cout << "\n游戏结束，再见！" << endl;
    system("pause");
    return 0;
}
