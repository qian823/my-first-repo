#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <iomanip>
#include <cmath>

using namespace std;

// 方程结构体
struct Equation {
    double a;  // x的系数
    double b;  // 常数项（左边）
    double c;  // 常数项（右边）
    string original;  // 原始方程字符串
};

// 去除字符串首尾空格
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}

// 判断是否为整数
bool isInteger(double num) {
    return fabs(num - round(num)) < 1e-9;
}

// 格式化数字（整数不显示小数，小数保留最多4位）
string formatNumber(double num) {
    if (isInteger(num)) {
        return to_string((long long)round(num));
    }
    // 检查是否为.0,.5,.25等简单小数
    ostringstream oss;
    oss << fixed << setprecision(4) << num;
    string result = oss.str();
    // 去除末尾的0
    while (result.back() == '0') {
        result.pop_back();
    }
    if (result.back() == '.') {
        result.pop_back();
    }
    return result;
}

// 解析方程
bool parseEquation(const string& input, Equation& eq) {
    eq.original = input;
    eq.a = 0;
    eq.b = 0;
    eq.c = 0;

    string eqStr = input;
    // 去除空格
    eqStr = regex_replace(eqStr, regex("\\s+"), "");

    // 找到等号
    size_t equalPos = eqStr.find('=');
    if (equalPos == string::npos) {
        cout << "错误：方程必须包含等号 '='。" << endl;
        return false;
    }

    string leftPart = eqStr.substr(0, equalPos);
    string rightPart = eqStr.substr(equalPos + 1);

    // 解析左边
    regex xTermRegex("([+-]?\\d*\\.?\\d*)x");
    regex constTermRegex("([+-]\\d+\\.?\\d*)");

    // 查找x项
    smatch match;
    string::const_iterator searchStart(leftPart.cbegin());
    while (regex_search(searchStart, leftPart.cend(), match, xTermRegex)) {
        string coefStr = match[1].str();
        double coef = 1.0;
        if (!coefStr.empty()) {
            if (coefStr == "+") coef = 1.0;
            else if (coefStr == "-") coef = -1.0;
            else coef = stod(coefStr);
        }
        eq.a += coef;
        searchStart = match.suffix().first;
    }

    // 查找常数项（在去除x项后）
    string leftNoX = regex_replace(leftPart, xTermRegex, "");
    // 在前面添加+号以便解析
    if (!leftNoX.empty() && leftNoX[0] != '+' && leftNoX[0] != '-') {
        leftNoX = "+" + leftNoX;
    }
    searchStart = leftNoX.cbegin();
    while (regex_search(searchStart, leftNoX.cend(), match, constTermRegex)) {
        eq.b += stod(match[1].str());
        searchStart = match.suffix().first;
    }

    // 解析右边
    double rightVal = stod(rightPart);
    eq.c = rightVal;

    return true;
}

// 展示解题步骤
void showSolvingSteps(const Equation& eq) {
    cout << "\n========== 解题步骤 ==========" << endl;
    cout << "原方程: " << eq.original << endl;

    // 转换为 ax + b = c 的形式
    string axStr, bStr, cStr;

    if (eq.a == 1) axStr = "x";
    else if (eq.a == -1) axStr = "-x";
    else if (isInteger(eq.a)) axStr = formatNumber(eq.a) + "x";
    else axStr = formatNumber(eq.a) + "x";

    if (eq.b >= 0) {
        bStr = " + " + formatNumber(eq.b);
    } else {
        bStr = " - " + formatNumber(-eq.b);
    }
    cStr = " = " + formatNumber(eq.c);

    // 显示标准形式
    string standardForm = axStr + (eq.b != 0 ? bStr : "") + cStr;
    cout << "整理: " << standardForm << endl;

    // 移项
    string moveStep;
    double rightResult;

    if (eq.b > 0) {
        moveStep = axStr + " = " + formatNumber(eq.c) + " - " + formatNumber(eq.b);
        rightResult = eq.c - eq.b;
    } else if (eq.b < 0) {
        moveStep = axStr + " = " + formatNumber(eq.c) + " + " + formatNumber(-eq.b);
        rightResult = eq.c + (-eq.b);
    } else {
        moveStep = axStr + " = " + formatNumber(eq.c);
        rightResult = eq.c;
    }
    cout << "移项: " << moveStep << endl;

    // 化简右边
    if (eq.b != 0) {
        string simplifiedRight = axStr + " = " + formatNumber(rightResult);
        cout << "化简: " << simplifiedRight << endl;
    }

    // 求解
    double result;
    if (eq.a == 0) {
        if (rightResult == 0) {
            cout << "\n答案: x 可取任意值（恒等式）" << endl;
        } else {
            cout << "\n答案: 无解（矛盾方程）" << endl;
        }
        cout << "==============================\n" << endl;
        return;
    }

    string solveStep;
    if (eq.a == 1) {
        solveStep = "x = " + formatNumber(rightResult);
        result = rightResult;
    } else if (eq.a == -1) {
        solveStep = "x = -" + formatNumber(rightResult);
        result = -rightResult;
    } else {
        solveStep = "x = " + formatNumber(rightResult) + " / " + formatNumber(eq.a);
        result = rightResult / eq.a;
    }
    cout << "求解: " << solveStep << endl;

    // 最终答案
    cout << "\n答案: x = " << formatNumber(result) << endl;
    cout << "==============================\n" << endl;
}

int main() {
    cout << "========== 一元一次方程求解器 ==========" << endl;
    cout << "支持格式:" << endl;
    cout << "  - ax + b = c (如: 2x + 3 = 7)" << endl;
    cout << "  - ax - b = c (如: 5x - 8 = 12)" << endl;
    cout << "  - ax = c (如: 3x = 15)" << endl;
    cout << "  - x + b = c (如: x + 5 = 10)" << endl;
    cout << "  - 支持小数 (如: 2.5x + 3 = 8)" << endl;
    cout << "========================================\n" << endl;

    while (true) {
        cout << "请输入一元一次方程 (输入 q 退出): ";
        string input;
        getline(cin, input);
        input = trim(input);

        if (input == "q" || input == "Q") {
            break;
        }

        if (input.empty()) {
            continue;
        }

        Equation eq;
        if (parseEquation(input, eq)) {
            showSolvingSteps(eq);
        }
    }

    cout << "\n程序结束，再见！" << endl;
    return 0;
}
