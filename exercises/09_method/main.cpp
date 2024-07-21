#include "../exercise.h"
#include <iostream>
#include <cassert>
struct Fibonacci {
    unsigned long long cache[128]={0};
    int cached=0;

    // TODO: 实现正确的缓存优化斐波那契计算
   unsigned long long get(int i) {
        if (i < 0 || i >= 128) {
            throw std::out_of_range("Index out of range");
        }

        // 如果值已经缓存，直接返回
        if (cached > i) {
            return cache[i];
        }

        // 基本情况
        if (cached == 0) {
            cache[0] = 0;
            cached++;
        }
        if (cached == 1) {
            cache[1] = 1;
            cached++;
        }

        // 计算并缓存 Fibonacci 数
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
            cached++;
        }

        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib;
    // fib.get(0);
    // fib.get(1);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
