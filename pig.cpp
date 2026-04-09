#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    cout << "========== 找出最大值 ==========" << endl;
    cout << "请输入若干个整数（空格分隔）: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    vector<int> arr;
    int num;

    while (ss >> num) {
        arr.push_back(num);
    }

    if (arr.empty()) {
        cout << "没有输入有效的数字！" << endl;
        system("pause");
        return 0;
    }

    // 找出最大值
    int maxVal = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    cout << "\n数组中的最大值是: " << maxVal << endl;

    system("pause");
    return 0;
}
