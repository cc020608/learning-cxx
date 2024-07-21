#include "../exercise.h"
#include <iostream>
#include <cassert>
// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(int i) {
    // 初始化缓存
    static unsigned long long cache[128] = {0}; // 默认初始化为 0
    static bool initialized = false;

    if (!initialized) {
        cache[0] = 0;
        cache[1] = 1;
        for (int j = 2; j < 128; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        initialized = true; // 标记为已初始化
    }

    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib100 = fibonacci(100);
    std::cout << "fibonacci(100) = " << fib100 << std::endl;
    ASSERT(fib100 == 3736710778780434371, "fibonacci(100) should be 3736710778780434371");
    return 0;
}
