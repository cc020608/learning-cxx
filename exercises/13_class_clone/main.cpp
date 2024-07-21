#include "../exercise.h"
#include <iostream>
#include <cassert>
// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;
public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]{}), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }
    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]), cached(other.cached), capacity(other.capacity) {
        std::copy(other.cache, other.cache + other.cached, cache); // 复制缓存数据
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

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
