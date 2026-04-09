#include <iostream>
#include <cmath>    // 用于浮点数精度判断、fabs()
#include <stdexcept> // 用于抛出异常（处理未定义情况）

// 模板函数：支持整数/浮点数底数，整数指数
template <typename T>
double power(T base, int exponent) {
    // 边界情况1：底数为0，指数为0（数学未定义）
    if (std::fabs(static_cast<double>(base)) < 1e-10 && exponent == 0) {
        throw std::invalid_argument("Error: 0^0 is undefined");
    }

    // 边界情况2：指数为0（任何非0数的0次方为1）
    if (exponent == 0) {
        return 1.0;
    }

    // 边界情况3：底数为0（0的正次方为0，负次方无意义）
    if (std::fabs(static_cast<double>(base)) < 1e-10) {
        if (exponent > 0) return 0.0;
        throw std::domain_error("Error: 0 raised to a negative power is undefined");
    }

    // 处理负指数：base^(-n) = 1/(base^n)
    bool is_negative_exponent = (exponent < 0);
    unsigned int abs_exponent = static_cast<unsigned int>(std::abs(exponent));

    double result = 1.0;
    double current_base = static_cast<double>(base); // 统一转为double计算，避免溢出

    // 快速幂算法（二进制 exponentiation）：时间复杂度 O(log|exponent|)
    while (abs_exponent > 0) {
        // 若当前指数位为1，乘以当前底数
        if (abs_exponent % 2 == 1) {
            result *= current_base;
        }
        // 底数平方，指数右移（除以2）
        current_base *= current_base;
        abs_exponent /= 2;
    }

    // 负指数：取倒数
    return is_negative_exponent ? 1.0 / result : result;
}

// 重载函数：专门处理浮点数指数（基于cmath的pow，但包装统一接口）
template <typename T1, typename T2>
double power(T1 base, T2 exponent) {
    static_assert(std::is_floating_point_v<T2>, "Exponent must be floating-point for this overload");
    
    // 处理0^0和0的负浮点数指数
    if (std::fabs(static_cast<double>(base)) < 1e-10) {
        if (std::fabs(static_cast<double>(exponent)) < 1e-10) {
            throw std::invalid_argument("Error: 0^0 is undefined");
        }
        if (exponent < 0) {
            throw std::domain_error("Error: 0 raised to a negative power is undefined");
        }
        return 0.0;
    }

    // 借助cmath的pow实现浮点数指数（已优化精度和特殊值）
    return std::pow(static_cast<double>(base), static_cast<double>(exponent));
}

// 测试函数
int main() {
    try {
        // 整数底数 + 整数指数
        std::cout << "2^3 = " << power(2, 3) << std::endl;          // 8.0
        std::cout << "5^-2 = " << power(5, -2) << std::endl;        // 0.04
        std::cout << "(-3)^4 = " << power(-3, 4) << std::endl;     // 81.0
        std::cout << "(-2)^3 = " << power(-2, 3) << std::endl;      // -8.0

        // 浮点数底数 + 整数指数
        std::cout << "2.5^2 = " << power(2.5, 2) << std::endl;      // 6.25
        std::cout << "1.5^-3 = " << power(1.5, -3) << std::endl;    // ~0.296296

        // 浮点数底数 + 浮点数指数
        std::cout << "4.0^0.5 = " << power(4.0, 0.5) << std::endl;  // 2.0（平方根）
        std::cout << "8.0^(1.0/3) = " << power(8.0, 1.0/3) << std::endl; // 2.0（立方根）
        std::cout << "2.0^1.5 = " << power(2.0, 1.5) << std::endl;  // ~2.82843

        // 边界情况测试（会抛出异常，注释掉可正常运行）
        // std::cout << "0^0 = " << power(0, 0) << std::endl;        // 抛出未定义异常
        // std::cout << "0^-2 = " << power(0, -2) << std::endl;      // 抛出定义域异常
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}