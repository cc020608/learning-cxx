#include "../exercise.h"
#include <iostream>
#include <cassert>
// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;
public:
    // TODO: 实现动态设置容量的构造器
   DynFibonacci(int capacity) : cache(new size_t[capacity]{}), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci()
    {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Index out of range");
        }

        // 如果 i 已缓存，直接返回
        if (cached > i) {
            return cache[i];
        }

        // 计算并缓存 Fibonacci 数
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1; // 更新已缓存的数量

        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
