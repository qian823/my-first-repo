#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>

using namespace std;

// 运算符列表
vector<char> ops = {'+', '-', '*', '/'};

// 存储所有解法（去重）
set<string> solutions;

// 将字母转换为数字
int charToNumber(char c) {
    c = toupper(c);
    switch (c) {
        case 'A': return 1;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return 0;
    }
}

// 将数字转换为显示字符（用于输出）
string numberToString(double num) {
    int intNum = static_cast<int>(num);
    if (abs(num - intNum) < 1e-6) {
        switch (intNum) {
            case 1: return "A";
            case 11: return "J";
            case 12: return "Q";
            case 13: return "K";
            default: return to_string(intNum);
        }
    }
    ostringstream oss;
    oss << num;
    return oss.str();
}

// 浮点数相等判断
bool isEquals(double a, double b) {
    return fabs(a - b) < 1e-6;
}

// 执行运算
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (fabs(b) < 1e-6) {
                return INFINITY;
            }
            return a / b;
        default: return 0;
    }
}

// 规范化表达式：处理交换律
// 对于加法和乘法，将操作数按字典序排列
string normalizeCommutative(const string& expr) {
    if (expr.empty()) return expr;
    if (expr[0] != '(') return expr;

    // 解析表达式 (left op right)
    int depth = 0;
    char op = '\0';
    size_t opPos = 0;

    for (size_t i = 1; i < expr.length() - 1; i++) {
        char c = expr[i];
        if (c == '(') depth++;
        else if (c == ')') depth--;
        else if (depth == 0 && (c == '+' || c == '-' || c == '*' || c == '/')) {
            op = c;
            opPos = i;
            break;
        }
    }

    if (op == '\0') {
        return normalizeCommutative(expr.substr(1, expr.length() - 2));
    }

    string left = expr.substr(1, opPos - 1);
    string right = expr.substr(opPos + 1, expr.length() - opPos - 2);

    string leftNorm = normalizeCommutative(left);
    string rightNorm = normalizeCommutative(right);

    // 处理交换律：加法和乘法按字典序排序
    if (op == '+' || op == '*') {
        if (leftNorm > rightNorm) {
            std::swap(leftNorm, rightNorm);
        }
    }

    // 特殊：* A 和 / A 本质相同（A=1）
    if (op == '/' && rightNorm == "A") {
        op = '*';
    }

    // 特殊：A * b 和 b * A 本质相同（交换律已处理）

    return "(" + leftNorm + " " + op + " " + rightNorm + ")";
}

// 简化表达式：去除不必要的外层括号
string simplifyExpr(const string& expr) {
    if (expr.empty()) return expr;
    if (expr[0] != '(' || expr.back() != ')') return expr;

    string inner = expr.substr(1, expr.length() - 2);

    // 检查是否可以安全去除
    int depth = 0;
    for (char c : inner) {
        if (c == '(') depth++;
        if (c == ')') depth--;
        if (depth < 0) return expr; // 不平衡，不能去除
    }

    // 如果内部没有同级运算符，可以去除
    char outerOp = '\0';
    for (char c : expr) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            outerOp = c;
            break;
        }
    }

    char innerOp = '\0';
    for (char c : inner) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            innerOp = c;
            break;
        }
    }

    // 如果内部没有括号，直接去除
    if (inner.find('(') == string::npos) {
        return inner;
    }

    // 如果外部是加/乘，内部是同优先级运算，可以去除
    if ((outerOp == '+' || outerOp == '*') && innerOp == outerOp) {
        return inner;
    }

    return expr;
}

// 递归查找所有解法
void findSolutionsDFS(vector<double> nums, vector<string> exprList) {
    if (nums.size() == 1) {
        if (isEquals(nums[0], 24.0)) {
            string canonical = normalizeCommutative(exprList[0]);
            string readable = simplifyExpr(canonical);
            solutions.insert(readable);
        }
        return;
    }

    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = i + 1; j < nums.size(); j++) {
            vector<double> newNumList;
            vector<string> newExprList;

            for (size_t k = 0; k < nums.size(); k++) {
                if (k != i && k != j) {
                    newNumList.push_back(nums[k]);
                    newExprList.push_back(exprList[k]);
                }
            }

            double a = nums[i];
            double b = nums[j];
            string exprA = exprList[i];
            string exprB = exprList[j];

            for (char op : ops) {
                // a op b
                double result1 = calculate(a, b, op);
                if (!isinf(result1)) {
                    string newExpr1 = "(" + exprA + " " + op + " " + exprB + ")";
                    vector<double> nextNumList1 = newNumList;
                    vector<string> nextExprList1 = newExprList;
                    nextNumList1.push_back(result1);
                    nextExprList1.push_back(newExpr1);
                    findSolutionsDFS(nextNumList1, nextExprList1);
                }

                // b op a (非交换运算)
                if (op == '-' || op == '/') {
                    double result2 = calculate(b, a, op);
                    if (!isinf(result2)) {
                        string newExpr2 = "(" + exprB + " " + op + " " + exprA + ")";
                        vector<double> nextNumList2 = newNumList;
                        vector<string> nextExprList2 = newExprList;
                        nextNumList2.push_back(result2);
                        nextExprList2.push_back(newExpr2);
                        findSolutionsDFS(nextNumList2, nextExprList2);
                    }
                }
            }
        }
    }
}

// 输入处理
void inputNumbers(vector<double>& nums) {
    cout << "请输入4个数字或字母(1-13, A/J/Q/K)，空格分隔: ";
    string input;
    getline(cin, input);
    istringstream iss(input);
    string token;
    int count = 0;

    while (iss >> token && count < 4) {
        if (token.length() == 1) {
            char c = token[0];
            if (isalpha(c)) {
                int num = charToNumber(c);
                if (num == 0) {
                    cout << "无效的字母 '" << c << "'，请使用 A/J/Q/K。" << endl;
                    nums.clear();
                    return;
                }
                nums.push_back(num);
                count++;
            } else if (isdigit(c)) {
                int num = c - '0';
                if (num >= 1 && num <= 9) {
                    nums.push_back(num);
                    count++;
                } else {
                    cout << "数字必须在1到13之间。" << endl;
                    nums.clear();
                    return;
                }
            } else {
                cout << "无效的输入: '" << c << "'" << endl;
                nums.clear();
                return;
            }
        } else {
            try {
                int num = stoi(token);
                if (num >= 1 && num <= 13) {
                    nums.push_back(num);
                    count++;
                } else {
                    cout << "数字必须在1到13之间。" << endl;
                    nums.clear();
                    return;
                }
            } catch (...) {
                cout << "无效的输入: '" << token << "'" << endl;
                nums.clear();
                return;
            }
        }
    }

    if (count != 4) {
        cout << "请输入完整的4个数字！" << endl;
        nums.clear();
    }
}

int main() {
    cout << "========== 24点游戏 ==========" << endl;
    cout << "规则: 输入4个数字(1-13)，使用加减乘除和括号计算得到24" << endl;
    cout << "支持字母: A=1, J=11, Q=12, K=13" << endl;
    cout << "已优化: 合并满足交换律、结合律的解法" << endl;
    cout << "===============================" << endl;

    while (true) {
        solutions.clear();
        vector<double> nums;
        inputNumbers(nums);

        if (nums.empty()) {
            continue;
        }

        vector<string> exprList;
        for (double num : nums) {
            exprList.push_back(numberToString(num));
        }

        cout << "\n正在计算..." << endl;
        findSolutionsDFS(nums, exprList);

        if (solutions.empty()) {
            cout << "\n很抱歉，无法用这4个数字计算出24。" << endl;
        } else {
            cout << "\n找到 " << solutions.size() << " 种本质不同的解法：" << endl;
            int idx = 1;
            for (const string& sol : solutions) {
                cout << idx << ". " << sol << " = 24" << endl;
                idx++;
            }
        }

        cout << "\n============================" << endl;
        string choice;
        cout << "是否继续？(y/n): ";
        cin >> choice;
        cin.ignore();
        if (choice != "y" && choice != "Y") {
            break;
        }
        cout << endl;
    }

    cout << "\n游戏结束，谢谢游玩！" << endl;
    return 0;
}
