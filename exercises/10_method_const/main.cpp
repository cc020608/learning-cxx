#include "../exercise.h"
#include <iostream>
#include <cassert>
struct Fibonacci {
   int numbers[11]; // 存储 Fibonacci 数

    // 修改方法签名和实现
    constexpr int get(int i)const {
        if (i < 0 || i > 10) {
            throw std::out_of_range("Index out of range");
        }
        return numbers[i]; // 返回对应的 Fibonacci 数
    }
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
